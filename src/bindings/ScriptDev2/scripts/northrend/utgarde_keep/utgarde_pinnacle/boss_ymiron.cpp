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
SDName: Boss_Ymiron
SD%Complete: 90%
SDComment:
SDAuthot: ScrappyDoo (c) Andeeria
SDCategory: Utgarde Pinnacle
EndScriptData */

#include "precompiled.h"
#include "utgarde_pinnacle.h"

enum Sounds
{
    SAY_AGGRO                   = -1575031,
    SAY_SUMMON_BJORN            = -1575032,
    SAY_SUMMON_HALDOR           = -1575033,
    SAY_SUMMON_RANULF           = -1575034,
    SAY_SUMMON_TORGYN           = -1575035,
    SAY_SLAY_1                  = -1575036,
    SAY_SLAY_2                  = -1575037,
    SAY_SLAY_3                  = -1575038,
    SAY_SLAY_4                  = -1575039,
    SAY_DEATH                   = -1575040
};

enum Spells
{
    SPELL_BANE                              = 48294,
    H_SPELL_BANE                            = 59301,
    SPELL_DARK_SLASH                        = 48292,
    SPELL_FETID_ROT                         = 48291,
    H_SPELL_FETID_ROT                       = 59300,
    SPELL_SCREAMS_OF_THE_DEAD               = 51750,
    SPELL_SPIRIT_BURST                      = 48529,
    H_SPELL_SPIRIT_BURST                    = 59305,
    SPELL_SPIRIT_STRIKE                     = 48423,
    H_SPELL_SPIRIT_STRIKE                   = 59304,
    SPELL_ANCESTORS_VENGEANCE               = 16939,

    SPELL_CHANNEL_SPIRIT_TO_YMIRON          = 48316,
    SPELL_CHANNEL_YMIRON_TO_SPIRIT          = 48307,

    SPELL_SPIRIT_FOUNT                      = 48380,
    H_SPELL_SPIRIT_FOUNT                    = 59320,

    SPELL_CHOOSE_SPIRIT                     = 48306,
    SPELL_TRANSFORM_SPIRIT_1                = 48308,
    SPELL_TRANSFORM_SPIRIT_2                = 48311,
    SPELL_TRANSFORM_SPIRIT_3                = 48312,
    SPELL_TRANSFORM_SPIRIT_4                = 48313,

    SPIRIT_DIES                             = 48596,

    SPELL_COSM_GHOST_TELEPORT               = 52096,


    SPELL_SUMMON_SPIRIT_FOUNT               = 48386,
    SPELL_AVENGING_SPIRITS                  = 48590
};

enum Creatures
{   
    CREATURE_BJORN_VISUAL                   = 27304,    
    CREATURE_HALDOR_VISUAL                  = 27310,    
    CREATURE_RANULF_VISUAL                  = 27311,    
    CREATURE_TORGYN_VISUAL                  = 27312,

    CREATURE_SPIRIT_FOUNT                   = 27339
};

uint32 Kings[4] = {DATA_BJORN, DATA_HALDOR, DATA_RANULF, DATA_TORGYN};

/*######
## boss_ymiron
######*/

struct MANGOS_DLL_DECL boss_ymironAI : public ScriptedAI
{
    boss_ymironAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    std::list<uint64> Summons;
    bool m_bIsRegularMode;
    bool bKingSequence;
    bool m_bIsBjorn;
    bool m_bIsHaldor;
    bool m_bIsRanulf;
    bool m_bIsTorgyn;
    bool bIsInRun;

    uint64 m_uiOrbGUID;
    uint32 m_uiPauseTimer;
    uint32 m_uiBaneTimer;
    uint32 m_uiFetidRotTimer; 
    uint32 m_uiDarkSlashTimer;
    uint32 m_uiAncestorsVengeanceTimer;
    uint32 m_uiOrbTargetChanger;
    uint32 m_uiAbilityBJORNTimer;
    uint32 m_uiAbilityRANULFTimer;
    uint32 m_uiAbilityTORGYNTimer;
    uint32 m_uiAbilityHALDORTimer;
    uint8  m_uiCurrentKing;
    uint32 m_uiThreshhold;
    uint8 subphase;

    void Reset()
    {
        m_bIsBjorn                  = false;
        m_bIsHaldor                 = false;
        m_bIsRanulf                 = false;
        m_bIsTorgyn                 = false;
        bKingSequence               = false;
        bIsInRun                    = false;
        m_uiFetidRotTimer           = urand(8000, 13000);
        m_uiBaneTimer               = urand(18000, 23000);
        m_uiDarkSlashTimer          = urand(28000, 33000);
        m_uiAncestorsVengeanceTimer = 50000;
        m_uiOrbTargetChanger        = 5000;
        m_uiOrbGUID                 = 0;
        m_uiCurrentKing             = 0;
        m_uiPauseTimer              = 0;
        m_uiThreshhold              = 80;
        subphase                    = 0;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

     void MovementInform(uint32 uiMotionType, uint32 uiPointId)
     {
         if (uiMotionType != POINT_MOTION_TYPE)
            return;

         if (!bKingSequence)
         {
             bIsInRun      = false;
             bKingSequence = true;
         }
     }


    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 3))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
            case 3: DoScriptText(SAY_SLAY_4, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void JustSummoned(Creature* pSummoned)
    {
        switch(pSummoned->GetEntry())
        {
            case CREATURE_SPIRIT_FOUNT:
                pSummoned->CastSpell(pSummoned, m_bIsRegularMode ? SPELL_SPIRIT_FOUNT : H_SPELL_SPIRIT_FOUNT, true);
                m_uiOrbGUID = pSummoned->GetGUID();
                m_uiOrbTargetChanger = 1000;
                break;
            default: break;
        }

        Summons.push_back(pSummoned->GetGUID());
    }

    void DespawnAdds()
    {
        if (!Summons.empty())
            for (std::list<uint64>::iterator itr = Summons.begin(); itr != Summons.end(); ++itr)
            {
                if (Creature* pSummoned = (Creature*)Unit::GetUnit((*m_creature), *itr))
                    pSummoned->ForcedDespawn();
            }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if(!m_creature->SelectHostileTarget() || !m_creature->getVictim() || !m_creature->isInCombat())
            return;

        if(bKingSequence)
        {
            if(m_uiPauseTimer < uiDiff)
            {
                m_creature->MonsterSay("zomed",LANG_UNIVERSAL,NULL);
                if (Creature* pKingHandler = (Creature*)Unit::GetUnit((*m_creature), m_pInstance->GetData64(Kings[m_uiCurrentKing])))
                {
                    m_creature->MonsterSay("glimps",LANG_UNIVERSAL,NULL);
                    switch(subphase)
                    {
                        case 0:
                        case 2:
                        case 4:
                        case 6:
                            m_uiThreshhold = m_uiThreshhold - 20;
                            m_creature->CastSpell(pKingHandler, SPELL_CHANNEL_YMIRON_TO_SPIRIT, true);
                            break;
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                            pKingHandler->CastSpell(m_creature, SPELL_CHANNEL_SPIRIT_TO_YMIRON, true);
                            ++m_uiCurrentKing;
                            bKingSequence = false;
                            bIsInRun = false;
                            SetCombatMovement(true);
                            break;
                        default: break;
                    }
                    ++subphase;
                }
                m_uiPauseTimer = 6000;
            }else m_uiPauseTimer -= uiDiff;
        }
        else if (!bIsInRun)
        {
            if(m_uiOrbTargetChanger < uiDiff)
            {
                Creature* pSpirit = (Creature*)Unit::GetUnit(*m_creature, m_uiOrbGUID);
                if(pSpirit && pSpirit->isAlive())
                    if(Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM, 0))
                        pSpirit->GetMotionMaster()->MoveChase(pPlayer);
                m_uiOrbTargetChanger = 15000;
            }else m_uiOrbTargetChanger -= uiDiff;

            if(m_uiBaneTimer < uiDiff)
            {
                DoCast(m_creature, m_bIsRegularMode ? SPELL_BANE : H_SPELL_BANE, true);
                m_uiBaneTimer = urand(15000, 20000);
            }else m_uiBaneTimer -= uiDiff;

            if(m_uiFetidRotTimer < uiDiff)
            {
                if(Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM,0))
                    m_creature->CastSpell(pPlayer, m_bIsRegularMode ? SPELL_FETID_ROT : H_SPELL_FETID_ROT, true);
                m_uiFetidRotTimer = urand(10000, 15000);
            }else m_uiFetidRotTimer -= uiDiff;

            if(m_uiDarkSlashTimer < uiDiff)
            {
                if(Unit* pUnit = m_creature->getVictim())
                {
                    int32 damage = int32(pUnit->GetMaxHealth() * 0.5);
                    m_creature->CastCustomSpell(pUnit, SPELL_DARK_SLASH, &damage, 0, 0, false); 
                }
                m_uiDarkSlashTimer = urand(30000, 35000);
            }else m_uiDarkSlashTimer -= uiDiff;

            if(m_uiAncestorsVengeanceTimer < uiDiff)
            {
                DoCast(m_creature, SPELL_ANCESTORS_VENGEANCE, false);
                m_uiAncestorsVengeanceTimer =  (m_bIsRegularMode ? urand(60000, 65000) : urand(45000, 50000));
            }else m_uiAncestorsVengeanceTimer -= uiDiff;

            if(m_bIsHaldor && m_uiAbilityHALDORTimer < uiDiff)
            {
                if(m_creature->getVictim())
                    m_creature->CastSpell(m_creature->getVictim(), m_bIsRegularMode ? SPELL_SPIRIT_STRIKE : H_SPELL_SPIRIT_STRIKE, true);
                m_uiAbilityHALDORTimer = 5000; // overtime
            } else m_uiAbilityHALDORTimer -= uiDiff;

            if(m_bIsTorgyn && m_uiAbilityTORGYNTimer <= uiDiff)
            {
                DoCast(m_creature, SPELL_AVENGING_SPIRITS, false);
                m_uiAbilityTORGYNTimer = 50000;
            }else m_uiAbilityTORGYNTimer -= uiDiff;

            if(m_bIsRanulf && m_uiAbilityRANULFTimer < uiDiff)
            {
                m_creature->CastSpell(m_creature, m_bIsRegularMode ? SPELL_SPIRIT_BURST : H_SPELL_SPIRIT_BURST, true);
                m_uiAbilityRANULFTimer = 10000;
            } else m_uiAbilityRANULFTimer -= uiDiff;

            if(m_bIsBjorn && m_uiAbilityBJORNTimer < uiDiff)
            {
                DoCast(m_creature, SPELL_SUMMON_SPIRIT_FOUNT, false);
                m_bIsBjorn = false;
            } else m_uiAbilityBJORNTimer -= uiDiff;

            if((m_creature->GetHealth() * 100 / m_creature->GetMaxHealth()) < m_uiThreshhold)
            {
                /*if(Creature* pSpirit = (Creature*)Unit::GetUnit(*m_creature, m_uiOrbGUID))
                {
                    pSpirit->setFaction(35);
                    pSpirit->ForcedDespawn();
                } */

                //if(m_creature->getVictim())
                //    m_creature->CastSpell(m_creature->getVictim(), SPELL_SCREAMS_OF_THE_DEAD, true);

                m_bIsBjorn  = false;
                m_bIsHaldor = false;
                m_bIsRanulf = false;
                m_bIsTorgyn = false;

                switch(m_uiCurrentKing)
                {
                    case 0: DoScriptText(SAY_SUMMON_BJORN, m_creature);  m_uiAbilityBJORNTimer  = 8000; m_bIsBjorn  = true; break;
                    case 1: DoScriptText(SAY_SUMMON_HALDOR, m_creature); m_uiAbilityHALDORTimer = 8000; m_bIsHaldor = true; break;
                    case 2: DoScriptText(SAY_SUMMON_RANULF, m_creature); m_uiAbilityRANULFTimer = 8000; m_bIsRanulf = true; break;
                    case 3: DoScriptText(SAY_SUMMON_TORGYN, m_creature); m_uiAbilityTORGYNTimer = 8000; m_bIsTorgyn = true; break;
                    default: break;
                }

                if (Creature* pKingHandler = (Creature*)Unit::GetUnit((*m_creature), m_pInstance->GetData64(Kings[m_uiCurrentKing])))
                {
                    float x, y, z;
                    pKingHandler->GetClosePoint(x, y, z, pKingHandler->GetObjectSize(), 2*INTERACTION_DISTANCE, pKingHandler->GetAngle(m_creature));
                    m_creature->GetMotionMaster()->MovePoint(0, x, y, z);
                    bIsInRun = true;
                }     
            }

            DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_ymiron(Creature* pCreature)
{
    return new boss_ymironAI(pCreature);
}

void AddSC_boss_ymiron()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_ymiron";
    newscript->GetAI = &GetAI_boss_ymiron;
    newscript->RegisterSelf();
}
