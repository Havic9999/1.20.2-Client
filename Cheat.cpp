#include "Cheat.h"
#include "Java.h"

#include <thread>
#include <chrono>

#include "Windows.h"
#include "iostream"
#include "GUI.h"

jclass getMinecraftClass()
{
	return ct.env->FindClass("eqv");
}

jobject getMinecraft()
{
	jfieldID getMinecraftField = ct.env->GetStaticFieldID(getMinecraftClass(), "E", "Leqv;"); //1.8.9 -> "A", "()Lave;"  1.20.2 -> "E", "Leqv;"
	return ct.env->GetStaticObjectField(getMinecraftClass(), getMinecraftField);
}

jobject getWorld()
{
	jfieldID getWorldField = ct.env->GetFieldID(getMinecraftClass(), "r", "Lfix;"); //1.8.9 ->  "f", "Lbdb;"  1.20.2 -> "E", "Lanf;"  |   "r", "Lfix;"
	return ct.env->GetObjectField(getMinecraft(), getWorldField);
}

jobject getPlayer()
{
	jfieldID getPlayerField = ct.env->GetFieldID(getMinecraftClass(), "s", "Lfng;"); //  1.8.9 -> "h", "Lbew;"  1.20.2 -> "s", "Lfng;"
	return ct.env->GetObjectField(getMinecraft(), getPlayerField);
}

void setPlayerSprint()
{
	if (!GetAsyncKeyState('W') || GetAsyncKeyState('S')) return;

	jmethodID setSprintingMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "g", "(Z)V"); // 1.8.9 -> "d", "(Z)V  1.20.2 -> "g", "(Z)V"
	
	ct.env->CallBooleanMethod(getPlayer(), setSprintingMethod, settings.sprint);
}

void setInvisible()
{
	jmethodID setInvisibleMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "j", "(Z)V"); // 1.8.9 -> "d", "(Z)V  1.20.2 -> "g", "(Z)V"

	ct.env->CallBooleanMethod(getPlayer(), setInvisibleMethod, settings.invisible);
}

void setOnGround()
{
	jmethodID setOnGroundMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "c", "(Z)V"); // 1.8.9 -> "d", "(Z)V  1.20.2 -> "g", "(Z)V"

	ct.env->CallBooleanMethod(getPlayer(), setOnGroundMethod, settings.onground);
}

void setNoGravity()
{
	jmethodID setNoGravityMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "e", "(Z)V"); 

	ct.env->CallBooleanMethod(getPlayer(), setNoGravityMethod, settings.gravity);
}

void setSwimming()
{
	jmethodID setSwimmingMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "h", "(Z)V");

	ct.env->CallBooleanMethod(getPlayer(), setSwimmingMethod, settings.swimming);
}

void isVisuallySwimming()
{
	jmethodID isVisuallySwimmingMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "bZ", "()Z");

	ct.env->CallBooleanMethod(getPlayer(), isVisuallySwimmingMethod, settings.visualswimming);
}

void isVisuallyCrawling()
{
	jmethodID isVisuallyCrawlingMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "ca", "()Z");

	ct.env->CallBooleanMethod(getPlayer(), isVisuallyCrawlingMethod, settings.visualcrawl);
}

void setAirSupply()
{
	jmethodID setAirSupplyMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "j", "(I)V");

	if (settings.airsupplybool == true)
	{
		ct.env->CallBooleanMethod(getPlayer(), setAirSupplyMethod, settings.airsupply);
	}
}


void canSprint()
{
	jmethodID canSprintMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "dE", "()Z");

	ct.env->CallBooleanMethod(getPlayer(), canSprintMethod, settings.cansprint);
}

void getBlockJumpFactor()
{
	jmethodID getBlockJumpFactorMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "aI", "()F");

	ct.env->CallBooleanMethod(getPlayer(), getBlockJumpFactorMethod, settings.jumpheight);
}

//"Entity": {

void runModules()
{

	while (true)
	{
		if (!getMinecraft()) continue;
		if (!getWorld()) continue;
		if (!getPlayer()) continue;

		

		if (settings.onground == true)
		{
			setPlayerSprint();
		}

		if (settings.onground == true)
		{
			setInvisible();
		}

		if (settings.onground == true)
		{
			setOnGround();
		}

		if (settings.gravity == true)
		{
			setNoGravity();
		}

		if (settings.swimming == true)
		{
			setSwimming();
		}

		if (settings.visualswimming == true)
		{
			isVisuallySwimming();
		}

		if (settings.visualcrawl == true)
		{
			isVisuallyCrawling();
		}

		if (settings.airsupply == true)
		{
			setAirSupply();
		}

		if (settings.cansprint == true)
		{
			canSprint();
		}

		if (settings.jumpheight == true)
		{
			getBlockJumpFactor();
		}

		std::cout << "Sprint: " << settings.sprint << std::endl;
		std::cout << "Invisible: " << settings.invisible << std::endl;
		std::cout << "Jump In Air: " << settings.onground << std::endl;
		std::cout << "No Gravity: " << settings.gravity << std::endl;
		std::cout << "Set Swimming: " << settings.swimming << std::endl;
		std::cout << "Swimming Animation: " << settings.visualswimming << std::endl;
		std::cout << "Crawling Animation: " << settings.visualcrawl << std::endl;
		std::cout << "Enable Infinite Air Supply: " << settings.airsupplybool << std::endl;
		std::cout << "Sprint (Sprint Any Time): " << settings.cansprint << std::endl;
		std::cout << "Air Supply Amount: " << settings.airsupply << std::endl;
		std::cout << "Jump Height: " << settings.jump << std::endl;
		std::cout << "Jump Height Value: " << settings.jumpheight << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
