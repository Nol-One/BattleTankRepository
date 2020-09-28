// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BatlleTankEditorTarget : TargetRules
{
	public BatlleTankEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "BatlleTank" } );

		bEnforceIWYU = true;
		bUseUnityBuild = false;
		bUsePCHFiles = false;
	}
}
