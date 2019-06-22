#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME CodingTDOnline_Android)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     Classes/HelloWorldScene.cpp
	 Classes/LoginScene.cpp
     Classes/ChooseCardScene.cpp
     Classes/GameScene.cpp
	 Classes/CardScene.cpp
	 Classes/CodeScene.cpp
	 Classes/LobbyScene.cpp
	 Classes/ListRoomScene.cpp
	 Classes/MyRoomScene.cpp
	 Classes/PlayerInformationScene.cpp
	 Classes/RankingScene.cpp
	 Classes/ResultScene.cpp
	 Classes/TutorialScene.cpp
	 
	 Classes/GlobalClass/Player.cpp
	 Classes/GlobalClass/SocketClient.cpp
	 Classes/GlobalClass/Tool.cpp
	 Classes/GlobalClass/Trophy.cpp
	 Classes/GlobalClass/Audio.cpp
	 
	 Classes/IngameObject/IngameObject.cpp
	 Classes/IngameObject/ObjectConstructor.cpp
	 Classes/IngameObject/SkillConstructor.cpp
	 
	 Classes/IngameObject/Skill/BaseSkillClass.cpp
	 Classes/IngameObject/Skill/BurningEnthusiasm.cpp
	 Classes/IngameObject/Skill/CoolBlooded.cpp
	 Classes/IngameObject/Skill/FireArmor.cpp
	 Classes/IngameObject/Skill/FrostNova.cpp
	 Classes/IngameObject/Skill/HeavenBless.cpp
	 Classes/IngameObject/Skill/HellFire.cpp
	 Classes/IngameObject/Skill/IceAge.cpp
	 Classes/IngameObject/Skill/NaturalWind.cpp
	 Classes/IngameObject/Skill/PassiveSkill.cpp
	 
	 Classes/IngameObject/Unit/BaseUnitClass.cpp
	 Classes/IngameObject/Unit/BlessedKingdom.cpp
	 Classes/IngameObject/Unit/CrazyWolf_1.cpp
	 Classes/IngameObject/Unit/CrazyWolf_2.cpp
	 Classes/IngameObject/Unit/CrazyWolf_3.cpp
	 Classes/IngameObject/Unit/DeadWalker_1.cpp
	 Classes/IngameObject/Unit/DeadWalker_2.cpp
	 Classes/IngameObject/Unit/DeadWalker_3.cpp
	 Classes/IngameObject/Unit/ElementalAlien_1.cpp
	 Classes/IngameObject/Unit/ElementalAlien_2.cpp
	 Classes/IngameObject/Unit/ElementalAlien_3.cpp
	 Classes/IngameObject/Unit/ElementalAlien_4.cpp
	 Classes/IngameObject/Unit/EnragedUrsa_1.cpp
	 Classes/IngameObject/Unit/EnragedUrsa_2.cpp
	 Classes/IngameObject/Unit/FlamedKingdom.cpp
	 Classes/IngameObject/Unit/FrozenKingdom.cpp
	 Classes/IngameObject/Unit/FrostWyvern_1.cpp
	 Classes/IngameObject/Unit/FrostWyvern_2.cpp
	 Classes/IngameObject/Unit/FrostWyvern_3.cpp
	 Classes/IngameObject/Unit/Helicopter_1.cpp
	 Classes/IngameObject/Unit/Helicopter_2.cpp
	 
	 Classes/IngameObject/Unit/HotheadedGunner_1.cpp
	 Classes/IngameObject/Unit/HotheadedGunner_2.cpp
	 Classes/IngameObject/Unit/HotheadedGunner_3.cpp
	 Classes/IngameObject/Unit/LiquidAssassin_1.cpp
	 Classes/IngameObject/Unit/LiquidAssassin_2.cpp
	 Classes/IngameObject/Unit/LiquidAssassin_3.cpp
	 Classes/IngameObject/Unit/PoisonousButterfly_1.cpp
	 Classes/IngameObject/Unit/PoisonousButterfly_2.cpp
	 Classes/IngameObject/Unit/PolarBear_1.cpp
	 Classes/IngameObject/Unit/PolarBear_2.cpp
	 Classes/IngameObject/Unit/PolarBear_3.cpp
	 Classes/IngameObject/Unit/UFODriver_1.cpp
	 Classes/IngameObject/Unit/UFODriver_2.cpp
	 Classes/IngameObject/Unit/UFODriver_3.cpp
	 Classes/IngameObject/Unit/UFODriver_4.cpp
	 Classes/IngameObject/Unit/VampireDragon_1.cpp
	 Classes/IngameObject/Unit/VampireDragon_2.cpp
	 Classes/IngameObject/Unit/Volcarona_1.cpp
	 Classes/IngameObject/Unit/Volcarona_2.cpp
	 Classes/IngameObject/Unit/WingedOrc_1.cpp
	 Classes/IngameObject/Unit/WingedOrc_2.cpp
	 Classes/IngameObject/Unit/WingedOrc_3.cpp	
     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/HelloWorldScene.h
	 Classes/LoginScene.h
     Classes/ChooseCardScene.h
     Classes/GameScene.h
	 Classes/CardScene.h
	 Classes/CodeScene.h
	 Classes/LobbyScene.h
	 Classes/ListRoomScene.h
	 Classes/MyRoomScene.h
	 Classes/PlayerInformationScene.h
	 Classes/RankingScene.h
	 Classes/ResultScene.h
	 Classes/TutorialScene.h
	  
	 Classes/GlobalClass/Player.h
	 Classes/GlobalClass/SocketClient.h
	 Classes/GlobalClass/Tool.h
	 Classes/GlobalClass/Trophy.h
	 Classes/GlobalClass/Audio.h
	 
	 Classes/IngameObject/IngameObject.h
	 Classes/IngameObject/ObjectConstructor.h
	 Classes/IngameObject/SkillConstructor.h
	
	 Classes/IngameObject/Skill/BaseSkillClass.h
	 Classes/IngameObject/Skill/BurningEnthusiasm.h
	 Classes/IngameObject/Skill/CoolBlooded.h
	 Classes/IngameObject/Skill/FireArmor.h
	 Classes/IngameObject/Skill/FrostNova.h
	 Classes/IngameObject/Skill/HeavenBless.h
	 Classes/IngameObject/Skill/HellFire.h
	 Classes/IngameObject/Skill/IceAge.h
	 Classes/IngameObject/Skill/NaturalWind.h
	 Classes/IngameObject/Skill/PassiveSkill.h
	 
	 Classes/IngameObject/Unit/BaseUnitClass.h
	 Classes/IngameObject/Unit/BlessedKingdom.h
	 Classes/IngameObject/Unit/CrazyWolf_1.h
	 Classes/IngameObject/Unit/CrazyWolf_2.h
	 Classes/IngameObject/Unit/CrazyWolf_3.h
	 Classes/IngameObject/Unit/DeadWalker_1.h
	 Classes/IngameObject/Unit/DeadWalker_2.h
	 Classes/IngameObject/Unit/DeadWalker_3.h
	 Classes/IngameObject/Unit/ElementalAlien_1.h
	 Classes/IngameObject/Unit/ElementalAlien_2.h
	 Classes/IngameObject/Unit/ElementalAlien_3.h
	 Classes/IngameObject/Unit/ElementalAlien_4.h
	 Classes/IngameObject/Unit/EnragedUrsa_1.h
	 Classes/IngameObject/Unit/EnragedUrsa_2.h
	 Classes/IngameObject/Unit/FlamedKingdom.h
	 Classes/IngameObject/Unit/FrozenKingdom.h
	 Classes/IngameObject/Unit/FrostWyvern_1.h
	 Classes/IngameObject/Unit/FrostWyvern_2.h
	 Classes/IngameObject/Unit/FrostWyvern_3.h
	 Classes/IngameObject/Unit/Helicopter_1.h
	 Classes/IngameObject/Unit/Helicopter_2.h
	 
	 Classes/IngameObject/Unit/HotheadedGunner_1.h
	 Classes/IngameObject/Unit/HotheadedGunner_2.h
	 Classes/IngameObject/Unit/HotheadedGunner_3.h
	 Classes/IngameObject/Unit/LiquidAssassin_1.h
	 Classes/IngameObject/Unit/LiquidAssassin_2.h
	 Classes/IngameObject/Unit/LiquidAssassin_3.h
	 Classes/IngameObject/Unit/PoisonousButterfly_1.h
	 Classes/IngameObject/Unit/PoisonousButterfly_2.h
	 Classes/IngameObject/Unit/PolarBear_1.h
	 Classes/IngameObject/Unit/PolarBear_2.h
	 Classes/IngameObject/Unit/PolarBear_3.h
	 Classes/IngameObject/Unit/UFODriver_1.h
	 Classes/IngameObject/Unit/UFODriver_2.h
	 Classes/IngameObject/Unit/UFODriver_3.h
	 Classes/IngameObject/Unit/UFODriver_4.h
	 Classes/IngameObject/Unit/VampireDragon_1.h
	 Classes/IngameObject/Unit/VampireDragon_2.h
	 Classes/IngameObject/Unit/Volcarona_1.h
	 Classes/IngameObject/Unit/Volcarona_2.h
	 Classes/IngameObject/Unit/WingedOrc_1.h
	 Classes/IngameObject/Unit/WingedOrc_2.h
	 Classes/IngameObject/Unit/WingedOrc_3.h	
	 
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_RES_DIR}/..)
endif()

if(LINUX OR WINDOWS)
    cocos_copy_res(COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
