// Fill out your copyright notice in the Description page of Project Settings.


#include "BagComponent.h"

#include "DataTableTool.h"
#include "FileTool.h"
#include "Inventory07/GlobalEventManager/GlobalEventManager.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UBagComponent::UBagComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBagComponent::BeginPlay()
{
	Super::BeginPlay();
	FGlobalEventManager::RegisterEvent(FName("InspectBagGridItemEvent"), this, FName("InspectBagGridItem"));
	FGlobalEventManager::RegisterEvent(FName("SortGridItemEvent"), this, FName("SortGridItem"));
	FGlobalEventManager::RegisterEvent(FName("StartPickupItemFromGroundEvent"), this, FName("StartPickupItemFromGround"));
}

void UBagComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	FGlobalEventManager::UnRegisterEvent(FName("InspectBagGridItemEvent"), this);
	FGlobalEventManager::UnRegisterEvent(FName("SortGridItemEvent"), this);
	FGlobalEventManager::UnRegisterEvent(FName("StartPickupItemFromGroundEvent"), this);
}


// Called every frame
void UBagComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBagComponent::InspectBagGridItem(int GridIndex)
{
	auto ViewID = FGameSaveTool::GetBagGridDataByIndex(GridIndex).ID;
	if (!FGameSaveTool::IsBagHadItem(ViewID))
	{
		FGameSaveTool::AddViewBagGridItemID(ViewID);
		FGlobalEventManager::TriggerEvent(FName("ViewBagGridItemFinishedEvent"), &ViewID);
	}
}

int UBagComponent::AddItem(int ID, int Amount)
{
	auto ItemInBagGridAttr = FDataTableTool::GetItemInBagGridAttr(IntToName(ID));
	if (ItemInBagGridAttr == nullptr)
	{
		return Amount;
	}

	int FoundIndex = FindFreeGridIndex(ID);

	// find a stack that is not full
	if (FoundIndex != -1)
	{
		int Total = FGameSaveTool::GetBagGridDataByIndex(FoundIndex).Num + Amount;
		FBagGridData NewBagGrid(ID, FMath::Min(Total, ItemInBagGridAttr->MaxStackNum));
		FGameSaveTool::SetBagGridDataByIndex(NewBagGrid, FoundIndex);
		
		// trigger event to update ui
		FGlobalEventManager::TriggerEvent(FName("AddItemOnBagGridEvent"), &FoundIndex);
		
		Amount = Total - NewBagGrid.Num;
		if (Amount == 0)
		{
			return 0;
		}
		else
		{
			return AddItem(ID, Amount);
		}
	}
	else // no stack available
	{
		// find empty grid
		FoundIndex = FindEmptyGridIndex();
		if (FoundIndex != -1)
		{
			FBagGridData NewBagGridData(ID, FMath::Min(Amount, ItemInBagGridAttr->MaxStackNum));
			FGameSaveTool::SetBagGridDataByIndex(NewBagGridData, FoundIndex);
			
			FGlobalEventManager::TriggerEvent(FName("AddItemOnBagGridEvent"), &FoundIndex);
		
			Amount -= NewBagGridData.Num;
			if (Amount == 0)
			{
				return 0;
			}
			else
			{
				return AddItem(ID, Amount);
			}
		}
		else // bag full
		{
			return Amount;
		}
	}
}

bool UBagComponent::SubItem(int ID, int Amount)
{
	check(ID != 0 || Amount > 0);
	int TotalNum = FGameSaveTool::GetItemInBagGridTotalNum(ID);
	if (TotalNum >= Amount)
	{
		int FoundIndex = FindMinNumGrid(ID);

		int FindGridNum = FGameSaveTool::GetBagGridDataByIndex(FoundIndex).Num;
		int NewItemNum = FindGridNum - FMath::Min(FindGridNum, Amount);
		Amount -= FMath::Min(FindGridNum, Amount);
		
		FBagGridData NewBagGrid(NewItemNum == 0 ? 0 : ID, NewItemNum);
		FGameSaveTool::SetBagGridDataByIndex(NewBagGrid, FoundIndex);

		// trigger event to update ui
		FGlobalEventManager::TriggerEvent(FName("SubItemOnBagGridEvent"), &FoundIndex);
		
		if (Amount == 0)
		{
			return true;
		}
		else
		{
			return SubItem(ID, Amount);
		}
	}
	
	return false;
}

void UBagComponent::SortGridItem()
{
	auto BagGridDatas = FGameSaveTool::GetAllBagGridDatas();
	
	// TMap<id, num> all items in bag
	TMap<int, int> AllItems;
	for (auto BagGridData : BagGridDatas)
	{
		if (BagGridData.ID == 0)
		{
			continue;
		}

		if (!AllItems.Contains(BagGridData.ID))
		{
			AllItems.Add(BagGridData.ID, BagGridData.Num);
		}
		else
		{
			*AllItems.Find(BagGridData.ID) += BagGridData.Num;
		}
	}
	// sort TMap by id incremently
	AllItems.KeySort([](int L, int R){ return L < R; });

	TArray<FBagGridData> NewBagGridDatas;
	for (auto KeyValuePair : AllItems)
	{
		// amount of grids that expect to be fully filled 
		int MaxStackNum = FDataTableTool::GetItemInBagGridAttr(FName(FString::FromInt(KeyValuePair.Key)))->MaxStackNum;
		int ExpectedFullGridNum = KeyValuePair.Value / MaxStackNum;
		for (int i = 0; i < ExpectedFullGridNum; ++i)
		{
			NewBagGridDatas.Add(FBagGridData(KeyValuePair.Key, MaxStackNum));
		}

		// after fully filled, the rest item amount
		int ExpectedNotFullGridItemNum = KeyValuePair.Value % MaxStackNum;
		if (ExpectedNotFullGridItemNum > 0)
		{
			NewBagGridDatas.Add(FBagGridData(KeyValuePair.Key, ExpectedNotFullGridItemNum));
		}
	}

	// null grid
	int NullGridNum = BagGridDatas.Num() - NewBagGridDatas.Num();
	for (int i = 0; i < NullGridNum; ++i)
	{
		NewBagGridDatas.Add(FBagGridData(0, 0));
	}

	FGameSaveTool::SetAllBagGridDatas(NewBagGridDatas);
	FGlobalEventManager::TriggerEvent(FName("SortCompleteEvent"), nullptr);
}

void UBagComponent::StartPickupItemFromGround(AActor *User, FName Index, FVector NewLocation)
{
	if (this->GetOwner() == User)
	{
		auto ItemOnGroundData = FGameSaveTool::GetItemOnGroundDataByIndex(Index);

		int RemainAmount = AddItem(ItemOnGroundData.ID, ItemOnGroundData.Num);

		struct 
		{
			int Remain;
			FName Index;
			FVector Location;
		} Params;
		Params.Index = Index;
		Params.Remain = RemainAmount;
		Params.Location = NewLocation;

		// to GameMode
		FGlobalEventManager::TriggerEvent(FName("EndPickupItemFromGroundEvent"), &Params);
	}

	
}

int UBagComponent::FindFreeGridIndex(int ID)
{
	int FoundIndex = -1;
	int MaxNum = -1;
	int MaxStackNum = FDataTableTool::GetItemInBagGridAttr(IntToName(ID))->MaxStackNum;
	
	auto BagGridDatas = FGameSaveTool::GetAllBagGridDatas();
	for (int i = 0; i < BagGridDatas.Num(); ++i)
	{
		if (BagGridDatas[i].ID != ID || BagGridDatas[i].Num == MaxStackNum)
		{
			continue;
		}
		
		if (MaxNum < BagGridDatas[i].Num)
		{
			MaxNum = BagGridDatas[i].Num;
			FoundIndex = i;
		}
	}
	

	return FoundIndex;
}

int UBagComponent::FindEmptyGridIndex()
{
	auto BagGridDatas = FGameSaveTool::GetAllBagGridDatas();
	for (int i = 0; i < BagGridDatas.Num(); ++i)
	{
		if (BagGridDatas[i].ID == 0)
		{
			return i;
		}
	}
	return -1;
}

int UBagComponent::FindMinNumGrid(int ID)
{
	int FoundIndex = -1;
	int MinNum = 9999999;
	auto BagGridDatas = FGameSaveTool::GetAllBagGridDatas();
	for (int i = 0; i < BagGridDatas.Num(); ++i)
	{
		if (BagGridDatas[i].ID != ID)
		{
			continue;
		}

		if (MinNum >= BagGridDatas[i].Num)
		{
			MinNum = BagGridDatas[i].Num;
			FoundIndex = i;
		}
	}
	return FoundIndex;
}