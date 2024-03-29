// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/MFA_ExampleProject

using UnrealBuildTool;

public class MFA_ExampleProjectEditorTarget : TargetRules
{
	public MFA_ExampleProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] { "MFA_ExampleProject" });
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
	}
}