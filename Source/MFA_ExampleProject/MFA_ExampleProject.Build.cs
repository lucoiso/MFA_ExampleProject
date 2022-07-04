// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/UEModularFeatures_ExtraActions

using UnrealBuildTool;

public class MFA_ExampleProject : ModuleRules
{
	public MFA_ExampleProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"CoreUObject",
			"Engine",
			"InputCore",
			"GameFeatures",
			"ModularGameplay",
			"GameplayAbilities",
			"EnhancedInput",
			"ModularFeatures_ExtraActions"
		});
	}
}