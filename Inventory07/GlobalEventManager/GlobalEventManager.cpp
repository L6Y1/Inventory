// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalEventManager.h"

TSharedPtr<FGlobalEventManager> FGlobalEventManager::Instance = nullptr;



void FGlobalEventManager::RegisterEvent(FName EventName, UObject *Obj, FName FunctionName)
{
	if (!FGlobalEventManager::GetInstance()->Events.Contains(EventName))
	{
		TArray<FScriptDelegate> Delegates;
		FScriptDelegate Delegate;
		
		Delegate.BindUFunction(Obj, FunctionName);
		Delegates.Add(Delegate);
		FGlobalEventManager::GetInstance()->Events.Add(EventName, Delegates);
		
	}
	else
	{
		FScriptDelegate Delegate;
		Delegate.BindUFunction(Obj, FunctionName);
		FGlobalEventManager::GetInstance()->Events.Find(EventName)->Add(Delegate);
	}
}

void FGlobalEventManager::UnRegisterEvent(FName EventName, UObject *Obj)
{
	if (FGlobalEventManager::GetInstance()->Events.Contains(EventName))
	{
		auto Delegates = *FGlobalEventManager::GetInstance()->Events.Find(EventName);
		for (int i = 0; i < Delegates.Num(); ++i)
		{
			if (Delegates[i].GetUObject() == Obj)
			{
				Delegates[i].Unbind();
				FGlobalEventManager::GetInstance()->Events.Find(EventName)->RemoveAt(i);
				--i;
			}
		}
		if (FGlobalEventManager::GetInstance()->Events.Find(EventName)->Num() == 0)
		{
			FGlobalEventManager::GetInstance()->Events.Remove(EventName);
		}
		
		
	}
	else
	{
		checkf(false, TEXT("Invalid EventName"));
	}
}

void FGlobalEventManager::TriggerEvent(FName EventName, void *Params)
{
	if (FGlobalEventManager::GetInstance()->Events.Contains(EventName))
	{
		auto Delegates= *FGlobalEventManager::GetInstance()->Events.Find(EventName);

		for (auto Delegate : Delegates)
		{
			if (Delegate.IsBound())
			{
				Delegate.ProcessDelegate<UObject>(Params);
			}
		}
		
		// for (int i = 0; i < Delegates.Num(); ++i)
		// {
		// 	if (IsValid(Delegates[i].GetUObject()))
		// 	{
		// 		Delegates[i].ProcessDelegate<UObject>(Params);
		// 	}
		// 	else
		// 	{
		// 		Delegates.RemoveAt(i);
		// 		--i;
		// 	}
		// }
	}
}
