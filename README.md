# DinoEatsHorseMaybe
![gamescreenshot](https://github.com/iWrote/DinoEatsHorseMaybe/blob/master/devLogsYay/screenCrop.png)

Put together in 8hrs for GMTK 2020. I was on 2 teams this time!!!


I'm really happy with the animation system i wrote/put_together! (See folders vox2spritesheet and src_anim)
![vox2spritesheet](https://github.com/iWrote/DinoEatsHorseMaybe/blob/master/devLogsYay/makingVox2Spritesheet.PNG)
A batch script sends a [MagicaVoxel](https://ephtracy.github.io/) .vox file into [IsoVox](https://github.com/tommyettinger/IsoVoxel) and then through [SpriteSheet Packer](https://amakaseev.github.io/sprite-sheet-packer/).
It produces a sprite sheet that's loaded into an animation component iWrote (:P) for use with [nlohmann::json](https://github.com/nlohmann/json) and [entt](https://github.com/skypjack/entt).
Unfortunately I wasn't comfortable enough with ECS and had to then awkwardly integrate it with my OOP code.

Here's a link to the game jam submission: https://varuns.itch.io/dinoeatshorsemaybe

Also see [Chris's game](https://christophergreeley.itch.io/strategy-goo)! It shares the same animation system (refactored beyond my comprehension :P) and some assets i made. Working with him really levelled up my C++ skillz haha
