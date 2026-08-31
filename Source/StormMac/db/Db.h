#pragma once

#include "rec/AchievementRec.h"
#include "rec/Cfg_CategoriesRec.h"
#include "rec/Cfg_ConfigsRec.h"
#include "rec/ChrRacesRec.h"
#include "WowClientDB.h"


extern WowClientDB<AchievementRec> g_achievementDB;
extern WowClientDB<Cfg_CategoriesRec> g_cfg_CategoriesDB;
extern WowClientDB<Cfg_ConfigsRec> g_cfg_ConfigsDB;
extern WowClientDB<ChrRacesRec> g_chrRacesDB;

void ClientDBInitialize();


