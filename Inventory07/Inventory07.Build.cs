// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Inventory07 : ModuleRules
{
	public Inventory07(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
				"UMG", "SlateCore", "Json", "interactive" 
				
			});
	}
}
