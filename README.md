# ChiLaXGlow

An unfinished open source hacking project for Counter-Strike: Global Offensive, based on the public glow ESP method. 

# Glow ESP

Glow is a built-in feature in source engine that can be enabled through developer console.
To activate it in-game, you have to enable developer console and insert the following commands:

1. sv_cheats 1
2. glow_outline_effect_enable 1

This will only work offline against bots, because the source engine doesn't allow the sv_cheats command in multiplayer lobbies. 
Thus, we will try to bypass this check and access the glow feature through memory altering. 

# Sources 

https://github.com/iseekwonderful/csgoGlow 

# Licenses

[GNU GPL v3.0](https://www.gnu.org/licenses/gpl-3.0)