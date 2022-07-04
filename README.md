# Unreal Engine Project: MFA_ExampleProject

![image](https://user-images.githubusercontent.com/77353979/177180834-62a1b78d-ea23-4301-bb8d-ec4953c3d230.png)

A simple example project for the [Modular Features Extra Actions plugin](https://github.com/lucoiso/UEModularFeatures_ExtraActions).

## Links:
* [Unreal Engine Forum](https://forums.unrealengine.com/t/free-modularfeatures-extraactions-plugin-modular-gas-enhanced-input-and-more/495400)
* [Plugin Repository](https://github.com/lucoiso/UEModularFeatures_ExtraActions)
* [Plugin on UE Marketplace](https://unrealengine.com/marketplace/en-US/product/modular-game-features-extra-actions)
* [Project Elementus](https://github.com/lucoiso/UEProject_Elementus) (Complete template with multiplayer support)

## What is in this project:

* **Modular Enhanced Inputs Actions and Mapping Context:**  
a) There's some Enhanced Input Actions available and two Modular Enhanced Input Mapping Contexts that can be added or removed at realtime. Files: Plugins/MFA_Abilities/MC_Abilities and Plugins/MFA_Abilities/MC_Movimentation.
* **Modular AttributeSet:**  
a) Created a single AttributeSet with a Stamina attribute that is being used as a dependency of Jump and Dash abilities (they cost stamina).
* **Modular GameplayAbilities:**  
a) Jump.  
b) Dash.
* **Modular GameplayEffect:**  
a) Stamina Regeneration: The main character will recover it's stamina over time.
* **Modular Actor Spawning:**  
a) Cube actors are spawned in the world if MFA_ActorSpawning modular feature is enabled.

## Modular Features:

1. **MFA_Abilities:** Adds abilities, attribute, effect and enhanced input mapping.
2. **MFA_Movimentation:** Adds enhanced input mapping.
3. **MFA_ActorSpawning:** Spawn the following actors: BP_Cube.
