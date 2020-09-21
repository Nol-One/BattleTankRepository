// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BatlleTank : ModuleRules
{
	public BatlleTank(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		bEnforceIWYU = true;
	}
}
