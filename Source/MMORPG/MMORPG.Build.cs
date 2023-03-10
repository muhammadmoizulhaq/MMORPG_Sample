// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MMORPG : ModuleRules
{
	public MMORPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG", "GameplayAbilities", "GameplayTags", "GameplayTasks" });

        PublicIncludePaths.AddRange(new string[]
        {
            "MMORPG",
            "MMORPG/Core",
            "MMORPG/Player",
            "MMORPG/UI",
            "MMORPG/Utils",
            "MMORPG/Data",
            "MMORPG/Data/Items",
            "MMORPG/AbilitySystem",
            "MMORPG/AbilitySystem/AttributeSet",
            "MMORPG/AbilitySystem/Abilities",
        });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
