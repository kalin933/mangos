/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Storm_Peaks
SD%Complete: 100
SDComment: Vendor Support (31247). Quest support: 12970, 12684
SDCategory: Storm Peaks
EndScriptData */

/* ContentData
mob_lightning_forge_credit
npc_loklira_the_crone
npc_roxi_ramrocket
npc_frostborn_scout
EndContentData */

#include "precompiled.h"

/*######
## mob_captive_mechagnome
######*/
enum
{
    QUEST_SLAVES_OF_THE_STORMFORGED     = 12957,
    SAY_FREED_1                         = -1999841,
    SAY_FREED_2                         = -1999840,
    SAY_FREED_3                         = -1999839,
    SAY_FREED_4                         = -1999838,
    SAY_FREED_5                         = -1999837,
    NPC_HOGUR_COLLECTOR                 = 29962, // according to DB used as QuestCredit
    POINT_ID                            = 1
};

float CaveEntrance[3] = {7833.33f, -99.26f, 881.51f};

#define GOSSIP_ITEM_MECHAGNOME "I'm not a laborer. I'm here to free you from  servitude in the mines"

struct MANGOS_DLL_DECL mob_captive_mechagnomeAI : public ScriptedAI
{
    mob_captive_mechagnomeAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool bFreed;
    bool bSpoke;
    bool bActed;
    uint8 uiAction;
    uint32 m_uiWaitTimer;
    uint64 m_uiPlayerGUID;

    void Reset() 
    {
        bFreed = false;
        bSpoke = false;
        bActed = false;
        uiAction = 0;
        m_uiWaitTimer = 2000;
        m_uiPlayerGUID = 0;
        m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE,EMOTE_STATE_WORK_MINING);
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == POINT_ID)
            m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (bFreed)
        {
            Player* pPlayer = (Player*)Unit::GetUnit((*m_creature),m_uiPlayerGUID);
            if (!pPlayer)
            {
                Reset();
                return;
            }

            if (m_uiWaitTimer <= uiDiff)
            {
                if (!bSpoke)
                {   
                    m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE,EMOTE_STATE_NONE);
                    if (pPlayer->GetQuestStatus(QUEST_SLAVES_OF_THE_STORMFORGED) == QUEST_STATUS_INCOMPLETE)
                        pPlayer->KilledMonsterCredit(NPC_HOGUR_COLLECTOR,m_creature->GetGUID());

                    uiAction = urand(0, 3);
                    switch (uiAction)
                    {
                        case 0: DoScriptText(urand(0, 1) ? SAY_FREED_2 : SAY_FREED_4,m_creature,pPlayer); break;
                        case 1: DoScriptText(SAY_FREED_5,m_creature,pPlayer); break;
                        case 2: DoScriptText(SAY_FREED_1,m_creature,pPlayer); break;
                        case 3: DoScriptText(SAY_FREED_3,m_creature,pPlayer); break;
                    }
                    m_uiWaitTimer = 3000;
                    bSpoke = true;
                    return;
                }

                if (!bActed)
                {
                    switch(uiAction)
                    {
                        // case walking out of cavern
                        case 0:        
                            float x, y, z, o;
                            o = m_creature->GetOrientation();
                            ((o >= M_PI)? o -= M_PI : o += M_PI);
                            m_creature->GetNearPoint(m_creature, x, y, z, m_creature->GetObjectSize(), INTERACTION_DISTANCE, o);
                            m_creature->GetMotionMaster()->MovePoint(POINT_ID, x, y, z);
                            break;
                        // case returning to work
                        case 1:
                            Reset();
                            return;
                        // case shuting down (despawning)
                        case 2:
                            m_creature->ForcedDespawn();
                            break;
                        // case following player. needs fourther reasearch if creature is assisting in combat
                        case 3:
                            m_creature->GetMotionMaster()->MoveFollow(pPlayer,PET_FOLLOW_DIST, PET_FOLLOW_ANGLE + urand(0,2)*M_PI/2);
                            break;
                    }
                    bActed = true;
                    bFreed = false;
                }
            }else m_uiWaitTimer -= uiDiff;
        }

        // if uiAction == 3 (following) and passed cave entrance
        if (m_creature->GetDistance(CaveEntrance[0],CaveEntrance[1],CaveEntrance[2]) < INTERACTION_DISTANCE)
            m_creature->ForcedDespawn();
    }

};

CreatureAI* GetAI_mob_captive_mechagnome(Creature* pCreature)
{
    return new mob_captive_mechagnomeAI(pCreature);
}

bool GossipHello_mob_captive_mechagnome(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_SLAVES_OF_THE_STORMFORGED) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MECHAGNOME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_mob_captive_mechagnome(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->CLOSE_GOSSIP_MENU();
            //pCreature->HandleEmoteCommand(EMOTE_STATE_NONE);
            ((mob_captive_mechagnomeAI*)pCreature->AI())->m_uiPlayerGUID = pPlayer->GetGUID();
            ((mob_captive_mechagnomeAI*)pCreature->AI())->bFreed = true;
            break;
    }
    return true;
}

/*######
## mob_lightning_forge_credit
######*/
enum
{
    QUEST_DESTROY_FORGES        = 12988,
    SPELL_BOULDERCRAGS_BOMB     = 56275,
    SPELL_EXPLOSION             = 59687
};

struct MANGOS_DLL_DECL mob_lightning_forge_creditAI : public ScriptedAI
{
    mob_lightning_forge_creditAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset() {}

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (!pCaster || !pSpell || pCaster->GetTypeId() != TYPEID_PLAYER || pSpell->Id != SPELL_BOULDERCRAGS_BOMB)
            return;

        DoCast(m_creature,SPELL_EXPLOSION,true);

        if (((Player*)pCaster)->GetQuestStatus(QUEST_DESTROY_FORGES) == QUEST_STATUS_INCOMPLETE)
            ((Player*)pCaster)->KilledMonsterCredit(m_creature->GetEntry(),m_creature->GetGUID());
    }

};

CreatureAI* GetAI_mob_lightning_forge_credit(Creature* pCreature)
{
    return new mob_lightning_forge_creditAI(pCreature);
}

/*######
## npc_frostborn_scout
######*/

enum Scout
{
    QUEST_MISSING_SCOUT          = 12864,

    GOSSIP_TEXTID_SCOUT_1        = 13611,
    GOSSIP_TEXTID_SCOUT_2        = 13612,
    GOSSIP_TEXTID_SCOUT_3        = 13613,
    GOSSIP_TEXTID_SCOUT_4        = 13614

};

#define GOSSIP_ITEM_SCOUT_1     "Are you okay? I've come to take you back to Frosthold if you can stand."
#define GOSSIP_ITEM_SCOUT_2     "I'm sorry that I didn't get here sooner. What happened?"
#define GOSSIP_ITEM_SCOUT_3     "I'll go get some help. Hang in there."

bool GossipHello_npc_frostborn_scout(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_MISSING_SCOUT) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SCOUT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SCOUT_1, pCreature->GetGUID());
        return true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_frostborn_scout(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SCOUT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SCOUT_2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SCOUT_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SCOUT_3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SCOUT_4, pCreature->GetGUID());
            pPlayer->AreaExploredOrEventHappens(QUEST_MISSING_SCOUT);
            break;
    }
    return true;
}

/*######
## npc_loklira_the_crone
######*/

#define GOSSIP_ITEM_TELL_ME         "Tell me about this proposal."
#define GOSSIP_ITEM_WHAT_HAPPENED   "What happened then?"
#define GOSSIP_ITEM_YOU_WANT_ME     "You want me to take part in the Hyldsmeet to end the war?"
#define GOSSIP_ITEM_VERY_WELL       "Very well. I'll take part in this competition."

enum
{
    GOSSIP_TEXTID_LOKLIRA1    = 13777,
    GOSSIP_TEXTID_LOKLIRA2    = 13778,
    GOSSIP_TEXTID_LOKLIRA3    = 13779,
    GOSSIP_TEXTID_LOKLIRA4    = 13780,

    QUEST_THE_HYLDSMEET       = 12970,

    CREDIT_LOKLIRA            = 30467
};

bool GossipHello_npc_loklira_the_crone(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_THE_HYLDSMEET) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TELL_ME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOKLIRA1, pCreature->GetGUID());
        return true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_loklira_the_crone(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WHAT_HAPPENED, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOKLIRA2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_YOU_WANT_ME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOKLIRA3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERY_WELL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOKLIRA4, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->TalkedToCreature(CREDIT_LOKLIRA, pCreature->GetGUID());
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
    return true;
}

/*######
## npc_thorim
######*/

#define GOSSIP_ITEM_THORIM1         "Can you tell me what became of Sif?"
#define GOSSIP_ITEM_THORIM2         "He did more than that, Thorim. He controls Ulduar now."
#define GOSSIP_ITEM_THORIM3         "It needn't end this way."

enum
{
    QUEST_SIBLING_RIVALRY           = 13064,

    SPELL_THORIM_STORY_KILL_CREDIT  = 56940,

    GOSSIP_TEXTID_THORIM1           = 13799,
    GOSSIP_TEXTID_THORIM2           = 13801,
    GOSSIP_TEXTID_THORIM3           = 13802,
    GOSSIP_TEXTID_THORIM4           = 13803
};

bool GossipHello_npc_thorim(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_SIBLING_RIVALRY) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THORIM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM1, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_thorim(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THORIM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THORIM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM4, pCreature->GetGUID());
            pCreature->CastSpell(pPlayer, SPELL_THORIM_STORY_KILL_CREDIT, true);
            break;
    }

    return true;
}

/*######
## npc_roxi_ramrocket
######*/

#define GOSSIP_TEXT_RAMROCKET1  "How do you fly in this cold climate?"
#define GOSSIP_TEXT_RAMROCKET2  "I hear you sell motorcycle parts."

enum
{
    SPELL_MECHANO_HOG           = 60866,
    SPELL_MEKGINEER_CHOPPER     = 60867
};

bool GossipHello_npc_roxi_ramrocket(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isTrainer())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_RAMROCKET1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    if (pCreature->isVendor())
    {
        if (pPlayer->HasSpell(SPELL_MECHANO_HOG) || pPlayer->HasSpell(SPELL_MEKGINEER_CHOPPER))
        {
            if (pPlayer->HasSkill(SKILL_ENGINERING) && pPlayer->GetBaseSkillValue(SKILL_ENGINERING) >= 450)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_RAMROCKET2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
        }
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_roxi_ramrocket(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_TRAIN:
            pPlayer->SEND_TRAINERLIST(pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_TRADE:
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
            break;
    }

    return true;
}

void AddSC_storm_peaks()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "mob_captive_mechagnome";
    newscript->GetAI = &GetAI_mob_captive_mechagnome;
    newscript->pGossipHello = &GossipHello_mob_captive_mechagnome;
    newscript->pGossipSelect = &GossipSelect_mob_captive_mechagnome;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_lightning_forge_credit";
    newscript->GetAI = &GetAI_mob_lightning_forge_credit;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_frostborn_scout";
    newscript->pGossipHello = &GossipHello_npc_frostborn_scout;
    newscript->pGossipSelect = &GossipSelect_npc_frostborn_scout;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_loklira_the_crone";
    newscript->pGossipHello = &GossipHello_npc_loklira_the_crone;
    newscript->pGossipSelect = &GossipSelect_npc_loklira_the_crone;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_thorim";
    newscript->pGossipHello = &GossipHello_npc_thorim;
    newscript->pGossipSelect = &GossipSelect_npc_thorim;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_roxi_ramrocket";
    newscript->pGossipHello = &GossipHello_npc_roxi_ramrocket;
    newscript->pGossipSelect = &GossipSelect_npc_roxi_ramrocket;
    newscript->RegisterSelf();
}
