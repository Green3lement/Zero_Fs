// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Maglev : ModuleRules
{
	public Maglev(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePaths.AddRange(
			new string[] {
				"C:\\Users\\Kyle VanSteelandt\\Documents\\Unreal Projects\\Zero_Fs\\Plugins\\Maglev\\Source\\Maglev\\Public",
				"Maglev\\Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"C:\\Users\\Kyle VanSteelandt\\Documents\\Unreal Projects\\Zero_Fs\\Plugins\\Maglev\\Source\\Maglev\\Private",
				"Maglev\\Private"
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				// ... add private dependencies that you statically link with here ...
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
