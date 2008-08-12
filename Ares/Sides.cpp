#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_NON_CONFORMING_SWPRINTFS
#endif
#pragma warning(disable: 4035)	//"no return value" - there is one, just not in our code ;)

#include "Sides.h"

//Static init
stdext::hash_map<SideClass*, Sides::SideExtensionStruct> Sides::SideExt;
stdext::hash_map<VoxClass*, DynamicVectorClass<Sides::VoxFileNameStruct> > Sides::EVAFiles;

//0x679A10
EXPORT Sides_LoadFromINI(REGISTERS* R)
{
	CCINIClass* pINI = (CCINIClass*)R->get_StackVar32(4);
	if(pINI)
	{
		for(int nSideIndex = 0; nSideIndex < SideClass::Array->get_Count(); nSideIndex++)
		{
			SideClass* pThis = (*SideClass::Array)[nSideIndex];
			char* pID = pThis->get_ID();

			if(_strcmpi(pID, "Civilian") && _strcmpi(pID, "Mutant"))
			{
				//defaults
				if(Sides::SideExt.find(pThis) == Sides::SideExt.end())
				{
					Sides::SideExtensionStruct Ext;

					//are these necessary?
					Ext.BaseDefenseCounts.Clear();
					Ext.BaseDefenses.Clear();
					Ext.ParaDrop.Clear();
					Ext.ParaDropNum.Clear();

					if(!_strcmpi(pID, "Nod"))	//Soviets
					{
						for(int i = 0; i < RulesClass::Global()->get_SovietBaseDefenseCounts()->get_Count(); i++)
							Ext.BaseDefenseCounts.AddItem((*RulesClass::Global()->get_SovietBaseDefenseCounts())[i]);
						for(int i = 0; i < RulesClass::Global()->get_SovietBaseDefenseCounts()->get_Count(); i++)
							Ext.BaseDefenseCounts.AddItem(RulesClass::Global()->get_SovietBaseDefenseCounts()->GetItem(i));

						for(int i = 0; i < RulesClass::Global()->get_SovietBaseDefenses()->get_Count(); i++)
							Ext.BaseDefenses.AddItem((*RulesClass::Global()->get_SovietBaseDefenses())[i]);
						for(int i = 0; i < RulesClass::Global()->get_SovietBaseDefenses()->get_Count(); i++)
							Ext.BaseDefenses.AddItem(RulesClass::Global()->get_SovietBaseDefenses()->GetItem(i));

						Ext.Crew = RulesClass::Global()->get_SovietCrew();
						Ext.DefaultDisguise = RulesClass::Global()->get_SovietDisguise();
						strcpy(Ext.EVATag, "Russian");
						Ext.LoadTextColor = ColorScheme::Find("SovietLoad");
						
						for(int i = 0; i < RulesClass::Global()->get_SovParaDropInf()->get_Count(); i++)
							Ext.ParaDrop.AddItem((*RulesClass::Global()->get_SovParaDropInf())[i]);
						for(int i = 0; i < RulesClass::Global()->get_SovParaDropInf()->get_Count(); i++)
							Ext.ParaDrop.AddItem((RulesClass::Global()->get_SovParaDropInf()->GetItem(i)));

						for(int i = 0; i < RulesClass::Global()->get_SovParaDropNum()->get_Count(); i++)
							Ext.ParaDropNum.AddItem((*RulesClass::Global()->get_SovParaDropNum())[i]);
						for(int i = 0; i < RulesClass::Global()->get_SovParaDropNum()->get_Count(); i++)
							Ext.ParaDropNum.AddItem(RulesClass::Global()->get_SovParaDropNum()->GetItem(i));

						Ext.PowerPlant = RulesClass::Global()->get_NodRegularPower();
						Ext.SidebarMixFileIndex = 1;
						Ext.SidebarYuriFileNames = false;
						Ext.SurvivorDivisor = RulesClass::Global()->get_SovietSurvivorDivisor();
					}
					else if(!_strcmpi(pID, "ThirdSide"))	//Yuri
					{
						for(int i = 0; i < RulesClass::Global()->get_ThirdBaseDefenseCounts()->get_Count(); i++)
							Ext.BaseDefenseCounts.AddItem((*RulesClass::Global()->get_ThirdBaseDefenseCounts())[i]);
						for(int i = 0; i < RulesClass::Global()->get_ThirdBaseDefenseCounts()->get_Count(); i++)
							Ext.BaseDefenseCounts.AddItem(RulesClass::Global()->get_ThirdBaseDefenseCounts()->GetItem(i));

						for(int i = 0; i < RulesClass::Global()->get_ThirdBaseDefenses()->get_Count(); i++)
							Ext.BaseDefenses.AddItem((*RulesClass::Global()->get_ThirdBaseDefenses())[i]);
						for(int i = 0; i < RulesClass::Global()->get_ThirdBaseDefenses()->get_Count(); i++)
							Ext.BaseDefenses.AddItem(RulesClass::Global()->get_ThirdBaseDefenses()->GetItem(i));

						Ext.Crew = RulesClass::Global()->get_ThirdCrew();
						Ext.DefaultDisguise = RulesClass::Global()->get_ThirdDisguise();
						strcpy(Ext.EVATag, "Yuri");
						Ext.LoadTextColor = ColorScheme::Find("SovietLoad");
						
						for(int i = 0; i < RulesClass::Global()->get_YuriParaDropInf()->get_Count(); i++)
							Ext.ParaDrop.AddItem((*RulesClass::Global()->get_YuriParaDropInf())[i]);
						for(int i = 0; i < RulesClass::Global()->get_YuriParaDropInf()->get_Count(); i++)
							Ext.ParaDrop.AddItem(RulesClass::Global()->get_YuriParaDropInf()->GetItem(i));

						for(int i = 0; i < RulesClass::Global()->get_YuriParaDropNum()->get_Count(); i++)
							Ext.ParaDropNum.AddItem((*RulesClass::Global()->get_YuriParaDropNum())[i]);
						for(int i = 0; i < RulesClass::Global()->get_YuriParaDropNum()->get_Count(); i++)
							Ext.ParaDropNum.AddItem(RulesClass::Global()->get_YuriParaDropNum()->GetItem(i));

						Ext.PowerPlant = RulesClass::Global()->get_ThirdPowerPlant();
						Ext.SidebarMixFileIndex = 1;
						Ext.SidebarYuriFileNames = true;
						Ext.SurvivorDivisor = RulesClass::Global()->get_ThirdSurvivorDivisor();
					}
					else //Allies or any other country
					{
						for(int i = 0; i < RulesClass::Global()->get_AlliedBaseDefenseCounts()->get_Count(); i++)
							Ext.BaseDefenseCounts.AddItem((*RulesClass::Global()->get_AlliedBaseDefenseCounts())[i]);
						for(int i = 0; i < RulesClass::Global()->get_AlliedBaseDefenseCounts()->get_Count(); i++)
							Ext.BaseDefenseCounts.AddItem(RulesClass::Global()->get_AlliedBaseDefenseCounts()->GetItem(i));

						for(int i = 0; i < RulesClass::Global()->get_AlliedBaseDefenses()->get_Count(); i++)
							Ext.BaseDefenses.AddItem((*RulesClass::Global()->get_AlliedBaseDefenses())[i]);
						for(int i = 0; i < RulesClass::Global()->get_AlliedBaseDefenses()->get_Count(); i++)
							Ext.BaseDefenses.AddItem(RulesClass::Global()->get_AlliedBaseDefenses()->GetItem(i));

						Ext.Crew = RulesClass::Global()->get_AlliedCrew();
						Ext.DefaultDisguise = RulesClass::Global()->get_AlliedDisguise();
						strcpy(Ext.EVATag, "Allied");
						Ext.LoadTextColor = ColorScheme::Find("AlliedLoad");
						
						for(int i = 0; i < RulesClass::Global()->get_AllyParaDropInf()->get_Count(); i++)
							Ext.ParaDrop.AddItem((*RulesClass::Global()->get_AllyParaDropInf())[i]);
						for(int i = 0; i < RulesClass::Global()->get_AllyParaDropInf()->get_Count(); i++)
							Ext.ParaDrop.AddItem(RulesClass::Global()->get_AllyParaDropInf()->GetItem(i));

						for(int i = 0; i < RulesClass::Global()->get_AllyParaDropNum()->get_Count(); i++)
							Ext.ParaDropNum.AddItem((*RulesClass::Global()->get_AllyParaDropNum())[i]);
						for(int i = 0; i < RulesClass::Global()->get_AllyParaDropNum()->get_Count(); i++)
							Ext.ParaDropNum.AddItem(RulesClass::Global()->get_AllyParaDropNum()->GetItem(i));

						Ext.PowerPlant = RulesClass::Global()->get_GDIPowerPlant();
						Ext.SidebarMixFileIndex = 0;
						Ext.SidebarYuriFileNames = false;
						Ext.SurvivorDivisor = RulesClass::Global()->get_AlliedSurvivorDivisor();
					}

					Sides::SideExt[pThis] = Ext;
				}
				
				Sides::SideExtensionStruct* pExt = &Sides::SideExt[pThis];
				if(pExt)
				{
					char buffer[0x200];
					char* p = NULL;

					ColorScheme* CS;

					if(pINI->ReadString(pID, "BaseDefenseCounts", "", buffer, 0x200))
					{
						pExt->BaseDefenseCounts.Clear();

						for(p = strtok(buffer, ","); p && *p; p = strtok(NULL, ","))
							pExt->BaseDefenseCounts.AddItem(atoi(p));
					}

					if(pINI->ReadString(pID, "BaseDefenses", "", buffer, 0x200))
					{
						pExt->BaseDefenses.Clear();

						for(p = strtok(buffer, ","); p && *p; p = strtok(NULL, ","))
							pExt->BaseDefenses.AddItem(BuildingTypeClass::FindOrAllocate(p));
					}

					if(pINI->ReadString(pID, "Crew", "", buffer, 0x80))
						pExt->Crew = InfantryTypeClass::FindOrAllocate(buffer);

					if(pINI->ReadString(pID, "DefaultDisguise", "", buffer, 0x80))
						pExt->DefaultDisguise = InfantryTypeClass::FindOrAllocate(buffer);

					if(pINI->ReadString(pID, "EVATag", "", buffer, 0x20))
						strncpy(pExt->EVATag, buffer, 0x20);

					if(pINI->ReadString(pID, "LoadTextColor", "", buffer, 0x80))
					{
						CS = ColorScheme::Find(buffer);
						if(CS)
							pExt->LoadTextColor = CS;
					}

					if(pINI->ReadString(pID, "ParaDropTypes", "", buffer, 0x200))
					{
						pExt->ParaDrop.Clear();

						for(p = strtok(buffer, ","); p && *p; p = strtok(NULL, ","))
						{
							TechnoTypeClass* pTT = UnitTypeClass::Find(p);
							
							if(!pTT)
								pTT = InfantryTypeClass::Find(p);

							if(pTT)
								pExt->ParaDrop.AddItem(pTT);
						}
					}

					if(pINI->ReadString(pID, "ParaDropNum", "", buffer, 0x200))
					{
						pExt->ParaDropNum.Clear();

						for(p = strtok(buffer, ","); p && *p; p = strtok(NULL, ","))
							pExt->ParaDropNum.AddItem(atoi(p));
					}

					if(pINI->ReadString(pID, "PowerPlant", "", buffer, 0x80))
						pExt->PowerPlant = BuildingTypeClass::FindOrAllocate(buffer);

					pExt->SidebarMixFileIndex = 
						pINI->ReadInteger(pID, "SidebarMixFileIndex", pExt->SidebarMixFileIndex);
					pExt->SidebarYuriFileNames = 
						pINI->ReadBool(pID, "SidebarYuriFileNames", pExt->SidebarYuriFileNames);
					pExt->SurvivorDivisor = 
						pINI->ReadInteger(pID, "SurvivorDivisor", pExt->SurvivorDivisor);
				}
			}
		}
	}
	return 0;
}

//0x4F8EC6
EXPORT Sides_BaseUnit(REGISTERS* R)
{
	HouseClass* pThis = (HouseClass*)R->get_ESI();

	if(pThis->get_OwnedBuildings() > 0)
		return 0x4F8F87;	//you survive

	for(int i = 0; i < RulesClass::Global()->get_BaseUnit()->get_Count(); i++)
		if(pThis->get_OwnedUnitTypes()->GetItemCount((*RulesClass::Global()->get_BaseUnit())[i]->get_ArrayIndex()) > 0)
	for(int i = 0; i < RulesClass::Global()->get_BaseUnit()->get_Count(); i++)
		if(pThis->get_OwnedUnitTypes()->GetItemCount(RulesClass::Global()->get_BaseUnit()->GetItem(i)->get_ArrayIndex()) > 0)
			return 0x4F8F87;	//you survive	
	
	return 0x4F8F79; //YOU LOSE!!!
}

//0x4F8C97
EXPORT Sides_BuildConst(REGISTERS* R)
{
	HouseClass* pThis = (HouseClass*)R->get_ESI();

	for(int i = 0; i < RulesClass::Global()->get_BuildConst()->get_Count(); i++)
		if(pThis->get_OwnedBuildingTypes1()->GetItemCount((*RulesClass::Global()->get_BuildConst())[i]->get_ArrayIndex()) > 0)
	for(int i = 0; i < RulesClass::Global()->get_BuildConst()->get_Count(); i++)
		if(pThis->get_OwnedBuildingTypes1()->GetItemCount(RulesClass::Global()->get_BuildConst()->GetItem(i)->get_ArrayIndex()) > 0)
			return 0x4F8D02;	//"low power"

	return 0x4F8DB1;
}

//0x4F8F54
EXPORT Sides_SlaveMinerCheck(REGISTERS* R)
{
	HouseClass* pThis = (HouseClass*)R->get_ESI();
	int n = R->get_EDI();

	for(int i = 0; i < RulesClass::Global()->get_BuildRefinery()->get_Count(); i++)
		if((*RulesClass::Global()->get_BuildRefinery())[i]->get_SlavesNumber() > 0)	//new sane way to find a slave miner
			n += pThis->get_OwnedBuildingTypes1()->GetItemCount((*RulesClass::Global()->get_BuildRefinery())[i]->get_ArrayIndex());
	for(int i = 0; i < RulesClass::Global()->get_BuildRefinery()->get_Count(); i++)
		if(RulesClass::Global()->get_BuildRefinery()->GetItem(i)->get_SlavesNumber() > 0)	//new sane way to find a slave miner
			n += pThis->get_OwnedBuildingTypes1()->GetItemCount(RulesClass::Global()->get_BuildRefinery()->GetItem(i)->get_ArrayIndex());

	R->set_EDI(n);
	return 0x4F8F75;
}

//0x4FE782
EXPORT Sides_PowerPlant(REGISTERS* R)
{
	HouseClass* pThis = (HouseClass*)R->get_EBP();

	int n = pThis->get_SideIndex();
	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		R->set_EDI((DWORD)Sides::SideExt[pSide].PowerPlant);
		return 0x4FE893;
	}
	else
		return 0;
}

//0x505C95
EXPORT Sides_BaseDefenseCounts(REGISTERS* R)
{
	HouseClass* pThis = (HouseClass*)R->get_EBX();
	int n = R->get_StackVar32(0x80);	//just to be on the safe side, we're not getting it from the House

	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		R->set_EAX(pThis->get_AIDifficulty());
		R->set_EDX((DWORD)Sides::SideExt[pSide].BaseDefenseCounts.get_Items());
		return 0x505CE6;
	}
	else
		return 0;
}

DWORD Sides::BaseDefenses(REGISTERS* R, DWORD dwReturnAddress)
{
	HouseTypeClass* pCountry = (HouseTypeClass*)R->get_EAX();

	int n = pCountry->get_SideIndex();
	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		R->set_EBX((DWORD)&Sides::SideExt[pSide].BaseDefenses);
		return dwReturnAddress;
	}
	else
		return 0;
}

//0x507BCA
EXPORT Sides_BaseDefenses1(REGISTERS* R)
	{ return Sides::BaseDefenses(R, 0x507C00); }

//0x507DBA
EXPORT Sides_BaseDefenses2(REGISTERS* R)
	{ return Sides::BaseDefenses(R, 0x507DF0); }

//0x507FAA
EXPORT Sides_BaseDefenses3(REGISTERS* R)
	{ return Sides::BaseDefenses(R, 0x507FE0); }

//0x52267D
EXPORT Sides_Disguise1(REGISTERS* R)
{
	HouseClass* pHouse = (HouseClass*)R->get_EAX();

	int n = pHouse->get_SideIndex();
	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		R->set_EAX((DWORD)Sides::SideExt[pSide].DefaultDisguise);
		return 0x5226B7;
	}
	else
		return 0;
}

DWORD Sides::Disguise(REGISTERS* R, DWORD dwReturnAddress, bool bUseESI)
{
	HouseClass* pHouse = (HouseClass*)R->get_EAX();
	InfantryClass* pThis;
	
	if(bUseESI)
		pThis = (InfantryClass*)R->get_ESI();
	else
		pThis = (InfantryClass*)R->get_ECX();

	int n = pHouse->get_SideIndex();
	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		pThis->set_Disguise(Sides::SideExt[pSide].DefaultDisguise);
		return dwReturnAddress;
	}
	else
		return 0;
}

//0x5227A3
EXPORT Sides_Disguise2(REGISTERS* R)
	{ return Sides::Disguise(R, 0x5227EC, false); }

//0x6F422F
EXPORT Sides_Disguise3(REGISTERS* R)
	{ return Sides::Disguise(R, 0x6F4277, true); }

//0x707D40
EXPORT Sides_Crew(REGISTERS* R)
{
	HouseClass* pHouse = (HouseClass*)R->get_ECX();

	int n = pHouse->get_SideIndex();
	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		R->set_ESI((DWORD)Sides::SideExt[pSide].Crew);
		return 0x707D81;
	}
	else
		return 0;
}

//0x451358
EXPORT Sides_SurvivorDivisor(REGISTERS* R)
{
	HouseClass* pHouse = (HouseClass*)R->get_EDX();

	int n = pHouse->get_SideIndex();
	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		R->set_ESI((DWORD)Sides::SideExt[pSide].SurvivorDivisor);
		return 0x451391;
	}
	else
		return 0;
}

DWORD Sides::LoadTextColor(REGISTERS* R, DWORD dwReturnAddress)
{
	int n = R->get_EAX();
	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		R->set_EAX((DWORD)Sides::SideExt[pSide].LoadTextColor);
		return dwReturnAddress;
	}
	else
		return 0;
}

//0x642B36
EXPORT Sides_LoadTextColor1(REGISTERS* R)
	{ return Sides::LoadTextColor(R, 0x68CAA9); }

//0x643BB9
EXPORT Sides_LoadTextColor2(REGISTERS* R)
	{ return Sides::LoadTextColor(R, 0x643BEF); }

//0x534FB1
EXPORT Sides_MixFileIndex(REGISTERS* R)
{
	int n = R->get_ESI();
	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
		R->set_ESI((DWORD)Sides::SideExt[pSide].SidebarMixFileIndex);
	else if(n == 2)
		R->set_ESI(1);

	return 0x534FBB;
}

DWORD Sides::MixFileYuriFiles(REGISTERS* R, DWORD dwReturnAddress1, DWORD dwReturnAddress2)
{
	BYTE* pScenario = (BYTE*)R->get_EAX();	//Scenario, upate this once mapped!
	int n = *((int*)(pScenario + 0x34B8));

	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		if(Sides::SideExt[pSide].SidebarYuriFileNames)
			return dwReturnAddress1;
		else
			return dwReturnAddress2;
	}
	else
		return 0;
}

//0x72FA1A
EXPORT Sides_MixFileYuriFiles1(REGISTERS* R)
	{ return Sides::MixFileYuriFiles(R, 0x72FA23, 0x72FA6A); }

//0x72F370
EXPORT Sides_MixFileYuriFiles2(REGISTERS* R)
	{ return Sides::MixFileYuriFiles(R, 0x72F379, 0x72F3A0); }

//0x72FBC3
EXPORT Sides_MixFileYuriFiles3(REGISTERS* R)
	{ return Sides::MixFileYuriFiles(R, 0x72FBCE, 0x72FBF5); }

//0x6CD3C1
EXPORT Sides_ParaDrop(REGISTERS* R)
{
	HouseClass* pHouse = ((SuperClass*)R->get_EBX())->get_Owner();

	int n = pHouse->get_SideIndex();
	SideClass* pSide = (*SideClass::Array)[n];

	if(Sides::SideExt.find(pSide) != Sides::SideExt.end())
	{
		Ares::SendPDPlane(
			pHouse,
			(CellClass*)R->get_EBP(),
			AircraftTypeClass::Array->GetItem(R->get_ESI()),
			&Sides::SideExt[pSide].ParaDrop,
			&Sides::SideExt[pSide].ParaDropNum);
		
		return 0x6CD500;
	}
	return 0;
}

//0x752F46
EXPORT Sides_LoadVoxFromINI(REGISTERS* R)
{
	VoxClass* pThis = (VoxClass*)R->get_ESI();
	CCINIClass* pINI = (CCINIClass*)R->get_EBP();

	Ares::Log("VoxClass::LoadFromINI (%s, pINI = 0x%08X)\n", pThis->get_Name(), pINI);

	DynamicVectorClass<Sides::VoxFileNameStruct> FileNames;
	Sides::VoxFileNameStruct vfn;
	char buffer[0x10] = "\0";
	
	for(int i = 0; i < SideClass::Array->get_Count(); i++)
	{
		if(Sides::SideExt.find((*SideClass::Array)[i]) != Sides::SideExt.end())
		{
			pINI->ReadString(
				pThis->get_Name(),
				Sides::SideExt[(*SideClass::Array)[i]].EVATag,
				"",
				buffer,
				0x10);

			strcpy(vfn.FileName, buffer);
		
			FileNames.AddItem(vfn);
		}
		else
		{
			*vfn.FileName = 0;
			FileNames.AddItem(vfn);	//make sure there's an entry for every side
		}
	}

	Sides::EVAFiles[pThis] = FileNames;
	return 0;
}

//0x7528E8
EXPORT Sides_LoadVoxFile(REGISTERS* R)
{
	VoxClass* pThis = (VoxClass*)R->get_EBP();
	if(Sides::EVAFiles.find(pThis) != Sides::EVAFiles.end())
	{
		int nSideIndex = *((int*)0xB1D4C8);

		R->set_EDI((DWORD)Sides::EVAFiles[pThis][nSideIndex].FileName);
		return 0x752901;
	}

	return 0;
}
