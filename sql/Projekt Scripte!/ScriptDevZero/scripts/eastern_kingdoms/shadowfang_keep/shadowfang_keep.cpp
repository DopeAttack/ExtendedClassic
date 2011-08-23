/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
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
SDName: Shadowfang_Keep
SD%Complete: 75
SDComment: npc_shadowfang_prisoner using escortAI for movement to door.
SDCategory: Shadowfang Keep
EndScriptData */

/* ContentData
npc_shadowfang_prisoner
mob_arugal_voidwalker
npc_arugal
boss_arugal
npc_deathstalker_vincent
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"
#include "shadowfang_keep.h"

/*######
## npc_shadowfang_prisoner
######*/

enum
{
    SAY_FREE_AS             = -1033000,
    SAY_OPEN_DOOR_AS        = -1033001,
    SAY_POST_DOOR_AS        = -1033002,
    EMOTE_VANISH_AS         = -1033014,
    SAY_FREE_AD             = -1033003,
    SAY_OPEN_DOOR_AD        = -1033004,
    SAY_POST1_DOOR_AD       = -1033005,
    SAY_POST2_DOOR_AD       = -1033006,
    EMOTE_UNLOCK_DOOR_AD    = -1033015,

    SPELL_UNLOCK            = 6421,
    SPELL_FIRE              = 6422,
    NPC_ASH                 = 3850,
    NPC_ADA                 = 3849
};

#define GOSSIP_ITEM_DOOR        "�ffnet bitte die T�r zum Hof."

struct MANGOS_DLL_DECL npc_shadowfang_prisonerAI : public npc_escortAI
{
    npc_shadowfang_prisonerAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiNpcEntry = pCreature->GetEntry();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_uiNpcEntry;

    void WaypointReached(uint32 uiPoint)
    {
        switch(uiPoint)
        {
            case 0:
                if (m_uiNpcEntry == NPC_ASH)
                    DoScriptText(SAY_FREE_AS, m_creature);
                else
                    DoScriptText(SAY_FREE_AD, m_creature);
                break;
            case 10:
                if (m_uiNpcEntry == NPC_ASH)
                    DoScriptText(SAY_OPEN_DOOR_AS, m_creature);
                else
                    DoScriptText(SAY_OPEN_DOOR_AD, m_creature);
                break;
            case 11:
                if (m_uiNpcEntry == NPC_ASH)
                    DoCastSpellIfCan(m_creature, SPELL_UNLOCK);
                else
                    DoScriptText(EMOTE_UNLOCK_DOOR_AD, m_creature);
                break;
            case 12:
                /* if (m_uiNpcEntry != NPC_ASH) [-ZERO] fix it
                    m_creature->HandleEmoteCommand(EMOTE_ONESHOT_USESTANDING); */
                break;
            case 13:
                if (m_uiNpcEntry == NPC_ASH)
                    DoScriptText(SAY_POST_DOOR_AS, m_creature);
                else
                    DoScriptText(SAY_POST1_DOOR_AD, m_creature);

                if (m_pInstance)
                    m_pInstance->SetData(TYPE_FREE_NPC, DONE);
                break;
            case 14:
                if (m_uiNpcEntry == NPC_ASH)
                    DoCastSpellIfCan(m_creature, SPELL_FIRE);
                else
                {
                    DoScriptText(SAY_POST2_DOOR_AD, m_creature);
                    SetRun();
                }
                break;
            case 15:
                if (m_uiNpcEntry == NPC_ASH)
                    DoScriptText(EMOTE_VANISH_AS, m_creature);
                break;
        }
    }

    void Reset() {}

    //let's prevent Adamant from charging into Ashcrombe's cell
    //and beating the crap out of him and vice versa XD
    void AttackStart(Unit* pWho)
    {
        if (pWho)
        {
            if (pWho->GetEntry() == NPC_ASH || pWho->GetEntry() == NPC_ADA)
                return;
            else
                ScriptedAI::AttackStart(pWho);
        }
    }
};

CreatureAI* GetAI_npc_shadowfang_prisoner(Creature* pCreature)
{
    return new npc_shadowfang_prisonerAI(pCreature);
}

bool GossipHello_npc_shadowfang_prisoner(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (pInstance && pInstance->GetData(TYPE_FREE_NPC) != DONE && pInstance->GetData(TYPE_RETHILGORE) == DONE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DOOR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_shadowfang_prisoner(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        if (npc_shadowfang_prisonerAI* pEscortAI = dynamic_cast<npc_shadowfang_prisonerAI*>(pCreature->AI()))
            pEscortAI->Start();
    }
    return true;
}

/*######
## mob_arugal_voidwalker
######*/

struct Waypoint
{
    float fX, fY, fZ;
};

//Cordinates for voidwalker spawns
static const Waypoint VWWaypoints[]=
{
    //fX        fY        fZ
    {-146.06f,  2172.84f, 127.953f},                        //this is the initial location, in the middle of the room
    {-159.547f, 2178.11f, 128.944f},                        //when they come back up, they hit this point then walk back down
    {-171.113f, 2182.69f, 129.255f},
    {-177.613f, 2175.59f, 128.161f},
    {-185.396f, 2178.35f, 126.413f},
    {-184.004f, 2188.31f, 124.122f},
    {-172.781f, 2188.71f, 121.611f},
    {-173.245f, 2176.93f, 119.085f},
    {-183.145f, 2176.04f, 116.995f},
    {-185.551f, 2185.77f, 114.784f},
    {-177.502f, 2190.75f, 112.681f},
    {-171.218f, 2182.61f, 110.314f},
    {-173.857f, 2175.1f,  109.255f}
};

enum
{
    LAST_WAYPOINT       = 12,

    NPC_VOIDWALKER      = 4627,

    SPELL_DARK_OFFERING = 7154
};

struct MANGOS_DLL_DECL mob_arugal_voidwalkerAI : public ScriptedAI
{
    mob_arugal_voidwalkerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsLeader = false;
        m_uiLeaderGUID = 0;
        m_uiCurrentPoint = 0;
        m_bReverse = false;
    }

    uint32 m_uiResetTimer, m_uiDarkOffering;
    uint8 m_uiCurrentPoint, m_uiPosition;                   //0 - leader, 1 - behind-right, 2 - behind, 3 - behind-left
    uint64 m_uiLeaderGUID;
    ScriptedInstance* m_pInstance;
    bool m_bIsLeader, m_bReverse, m_bWPDone;

    void Reset()
    {
        m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);
        m_uiDarkOffering = urand(4400,12500);
        m_bWPDone = true;

        Creature* pLeader = m_creature->GetMap()->GetCreature(m_uiLeaderGUID);
        if (pLeader && pLeader->isAlive())
        {
            m_creature->GetMotionMaster()->MoveFollow(pLeader, 1.0f, M_PI/2*m_uiPosition);
        }
        else
        {
            std::list<Creature*> lVoidwalkerList;
            Creature* pNewLeader = NULL;
            uint8 uiHighestPosition = 0;
            GetCreatureListWithEntryInGrid(lVoidwalkerList, m_creature, NPC_VOIDWALKER, 50.0f);
            for(std::list<Creature*>::iterator itr = lVoidwalkerList.begin(); itr != lVoidwalkerList.end(); ++itr)
            {
                if ((*itr)->isAlive())
                {
                    if (mob_arugal_voidwalkerAI* pVoidwalkerAI = dynamic_cast<mob_arugal_voidwalkerAI*>((*itr)->AI()))
                    {
                        uint8 uiPosition = pVoidwalkerAI->GetPosition();
                        if (uiPosition > uiHighestPosition)
                        {
                            pNewLeader = (*itr);
                            uiHighestPosition = uiPosition;
                        }
                    }
                }
            }

            if (pNewLeader)
            {
                m_uiLeaderGUID = pNewLeader->GetGUID();
                if (pNewLeader == m_creature)
                {
                    m_bIsLeader = true;
                    m_bWPDone = true;
                }
                else
                    m_creature->GetMotionMaster()->MoveFollow(pNewLeader, 1.0f, M_PI/2*m_uiPosition);
            }
            else
            {
                pNewLeader = m_creature;
                m_bIsLeader = true;
                m_bWPDone = true;
            }
        }
    }

    //this is the ACID script converted into C++
    //unfortunately, we can't have both AIs at the same time :(
    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bIsLeader && m_bWPDone)
        {
            m_creature->GetMotionMaster()->MovePoint(m_uiCurrentPoint, VWWaypoints[m_uiCurrentPoint].fX,
                VWWaypoints[m_uiCurrentPoint].fY, VWWaypoints[m_uiCurrentPoint].fZ);
            m_bWPDone = false;
        }

        if (!m_creature->isInCombat())
            return;

        if (m_uiDarkOffering < uiDiff)
        {
            m_uiDarkOffering = urand(4400,12500);

            if (Unit* pUnit = DoSelectLowestHpFriendly(10.0f, 290))
                DoCastSpellIfCan(pUnit, SPELL_DARK_OFFERING);
        }
        else
            m_uiDarkOffering -= uiDiff;

        //Check if we have a current target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }

    void MovementInform(uint32 uiMoveType, uint32 uiPointId)
    {
        if (uiMoveType != POINT_MOTION_TYPE || !m_bIsLeader)
            return;

        switch(uiPointId)
        {
            case 1:
                if (m_bReverse)
                    m_bReverse = false;
                break;
            case LAST_WAYPOINT:
                if (!m_bReverse)
                    m_bReverse = true;
                break;
        }

        if (m_bReverse)
            --m_uiCurrentPoint;
        else
            ++m_uiCurrentPoint;

        m_bWPDone = true;

        SendWaypoint();
    }

    void JustDied(Unit* /*pKiller*/)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_VOIDWALKER,DONE);
    }

    void SetPosition(uint8 uiPosition, Creature* pLeader)
    {
        m_uiPosition = uiPosition;

        if (!uiPosition)
            m_bIsLeader = true;
        else
            pLeader ? m_uiLeaderGUID = pLeader->GetGUID() : m_uiLeaderGUID = 0;

        Reset();
    }

    uint8 GetPosition()
    {
        return m_uiPosition;
    }

    void SendWaypoint()
    {
        std::list<Creature*> lVoidwalkerList;
        GetCreatureListWithEntryInGrid(lVoidwalkerList, m_creature, NPC_VOIDWALKER, 50.0f);
        for(std::list<Creature*>::iterator itr = lVoidwalkerList.begin(); itr != lVoidwalkerList.end(); ++itr)
        {
            if ((*itr)->isAlive())
                if (mob_arugal_voidwalkerAI* pVoidwalkerAI = dynamic_cast<mob_arugal_voidwalkerAI*>((*itr)->AI()))
                    pVoidwalkerAI->ReceiveWaypoint(m_uiCurrentPoint, m_bReverse);
        }
    }

    void ReceiveWaypoint(uint32 uiNewPoint, bool bReverse)
    {
        m_uiCurrentPoint = uiNewPoint;
        m_bReverse = bReverse;
    }

    void EnterEvadeMode()
    {
        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop(true);
        m_creature->LoadCreatureAddon();

        m_creature->SetLootRecipient(NULL);

        Reset();
    }
};

CreatureAI* GetAI_mob_arugal_voidwalker(Creature* pCreature)
{
    return new mob_arugal_voidwalkerAI(pCreature);
}

/*######
## boss_arugal
######*/

enum
{
    SPELL_VOID_BOLT                 = 7588,
    SPELL_SHADOW_PORT_UPPER_LEDGE   = 7587,
    SPELL_SHADOW_PORT_SPAWN_LEDGE   = 7586,
    SPELL_SHADOW_PORT_STAIRS        = 7136,
    SPELL_ARUGALS_CURSE             = 7621,
    SPELL_THUNDERSHOCK              = 7803,

    YELL_AGGRO                      = -1033017,
    YELL_KILLED_PLAYER              = -1033018,
    YELL_COMBAT                     = -1033019,
    YELL_FENRUS                     = -1033013
};

enum ArugalPosition
{
    POSITION_SPAWN_LEDGE = 1,
    POSITION_UPPER_LEDGE,
    POSITION_STAIRS
};

struct SpawnPoint
{
    float fX, fY, fZ, fO;
};

//Cordinates for voidwalker spawns
static const SpawnPoint VWSpawns[]=
{
    //fX        fY         fZ        fO
    {-155.352f, 2172.780f, 128.448f, 4.679f},
    {-147.059f, 2163.193f, 128.696f, 0.128f},
    {-148.869f, 2180.859f, 128.448f, 1.814f},
    {-140.203f, 2175.263f, 128.448f, 0.373f},
};

//roughly the height of Fenrus' room,
//used to tell how he should behave
const float HEIGHT_FENRUS_ROOM      = 140.0f;

struct MANGOS_DLL_DECL boss_arugalAI : public ScriptedAI
{
    boss_arugalAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

        if (pCreature->GetPositionZ() < HEIGHT_FENRUS_ROOM)
        {
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetVisibility(VISIBILITY_OFF);
            m_bEventMode = true;
        }
        else
            m_bEventMode = false;

        Reset();
    }

    ScriptedInstance* m_pInstance;
    ArugalPosition m_posPosition;
    uint32 m_uiTeleportTimer, m_uiCurseTimer, m_uiVoidboltTimer, m_uiThundershockTimer, m_uiYellTimer, m_uiSpeechTimer;
    uint8 m_uiSpeechStep;
    bool m_bAttacking, m_bEventMode;

    void Reset()
    {
        m_uiTeleportTimer = urand(22000, 26000);
        m_uiCurseTimer = urand(20000, 30000);
        m_uiVoidboltTimer = m_uiThundershockTimer = m_uiSpeechTimer = 0;
        m_uiYellTimer = urand(32000, 46000);
        m_bAttacking = true;
        m_posPosition = POSITION_SPAWN_LEDGE;
        m_uiSpeechStep = 1;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(YELL_AGGRO, m_creature);
        DoCastSpellIfCan(pWho, SPELL_VOID_BOLT);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            DoScriptText(YELL_KILLED_PLAYER, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bEventMode)
        {
            if (!m_uiSpeechStep)
                return;

            if (m_uiSpeechTimer < uiDiff)
            {
                switch(m_uiSpeechStep)
                {
                    case 1:
                        DoScriptText(YELL_FENRUS, m_creature);
                        m_creature->SetVisibility(VISIBILITY_ON);
                        m_uiSpeechTimer = 2000;
                        break;
                    case 2:
                        DoCastSpellIfCan(m_creature, SPELL_FIRE);
                        m_uiSpeechTimer = 5000;
                        break;
                    case 3:
                        if (m_pInstance)
                            if (GameObject* pLightning = m_creature->GetMap()->GetGameObject(m_pInstance->GetData64(DATA_LIGHTNING)))
                                pLightning->Use(m_creature);

                        m_uiSpeechTimer = 5000;
                        break;
                    case 4:
                        m_creature->SetVisibility(VISIBILITY_OFF);
                        m_uiSpeechTimer = 500;
                        break;
                    case 5:
                        Creature *pVoidwalker, *pLeader;
                        pVoidwalker = pLeader = NULL;

                        for(uint8 i = 0; i < 4; i++)
                        {
                            pVoidwalker = m_creature->SummonCreature(NPC_VOIDWALKER,VWSpawns[i].fX,
                                VWSpawns[i].fY, VWSpawns[i].fZ, VWSpawns[i].fO, TEMPSUMMON_DEAD_DESPAWN, 1);

                            if (!pVoidwalker)
                                continue;

                            if (!i)
                                pLeader = pVoidwalker;

                            if (mob_arugal_voidwalkerAI* pVoidwalkerAI = dynamic_cast<mob_arugal_voidwalkerAI*>(pVoidwalker->AI()))
                                pVoidwalkerAI->SetPosition(i,pLeader);

                            pVoidwalker = NULL;
                        }
                        m_uiSpeechStep = 0;
                        return;
                    default:
                        m_uiSpeechStep = 0;
                        return;
                }
                ++m_uiSpeechStep;
            }
            else
                m_uiSpeechTimer -= uiDiff;

            return;
        }

        //Check if we have a current target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (GetManaPercent() < 6.0f && !m_bAttacking)
        {
            if (m_posPosition != POSITION_UPPER_LEDGE)
                StartAttacking();
            else if (m_uiTeleportTimer > 2000)
                m_uiTeleportTimer = 2000;

            m_bAttacking = true;
        }
        else if (GetManaPercent() > 12.0f && m_bAttacking)
        {
            StopAttacking();
            m_bAttacking = false;
        }

        if (m_uiYellTimer < uiDiff)
        {
            DoScriptText(YELL_COMBAT, m_creature);
            m_uiYellTimer = urand(34000, 68000);
        }
        else
            m_uiYellTimer -= uiDiff;

        if (m_uiCurseTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                DoCastSpellIfCan(pTarget, SPELL_ARUGALS_CURSE);

            m_uiCurseTimer = urand(20000, 35000);
        }
        else
            m_uiCurseTimer -= uiDiff;

        if (m_uiThundershockTimer < uiDiff)
        {
            if (GetVictimDistance() < 5.0f)
            {
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_THUNDERSHOCK);
                m_uiThundershockTimer = urand(30200, 38500);
            }
        }
        else
            m_uiThundershockTimer -= uiDiff;

        if (m_uiVoidboltTimer < uiDiff)
        {
            if (!m_bAttacking)
            {
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_VOID_BOLT);
                m_uiVoidboltTimer = urand(2900, 4800);
            }
        }
        else
            m_uiVoidboltTimer -= uiDiff;

        if (m_uiTeleportTimer < uiDiff)
        {
            ArugalPosition posNewPosition;

            if (m_posPosition == POSITION_SPAWN_LEDGE)
                posNewPosition = (ArugalPosition)urand(2, 3);
            else
            {
                posNewPosition = (ArugalPosition)urand(1, 2);

                if (m_posPosition == posNewPosition)
                    posNewPosition = POSITION_STAIRS;
            }

            if (m_creature->IsNonMeleeSpellCasted(false))
                m_creature->InterruptNonMeleeSpells(false);

            switch(posNewPosition)
            {
                case POSITION_SPAWN_LEDGE:
                    DoCastSpellIfCan(m_creature, SPELL_SHADOW_PORT_SPAWN_LEDGE, true);
                    break;
                case POSITION_UPPER_LEDGE:
                    DoCastSpellIfCan(m_creature, SPELL_SHADOW_PORT_UPPER_LEDGE, true);
                    break;
                case POSITION_STAIRS:
                    DoCastSpellIfCan(m_creature, SPELL_SHADOW_PORT_STAIRS, true);
                    break;
            }

            if (GetManaPercent() < 6.0f)
            {
                if (posNewPosition == POSITION_UPPER_LEDGE)
                {
                    StopAttacking();
                    m_uiTeleportTimer = urand(2000, 2200);
                }
                else
                {
                    StartAttacking();
                    m_uiTeleportTimer = urand(48000, 55000);
                }
            }
            else
                m_uiTeleportTimer = urand(48000, 55000);

            m_posPosition = posNewPosition;
        }
        else
            m_uiTeleportTimer -= uiDiff;

        if (m_bAttacking)
            DoMeleeAttackIfReady();
    }

    void AttackStart(Unit* pWho)
    {
        if (!m_bEventMode)
            ScriptedAI::AttackStart(pWho);
    }

    //make the code nice and pleasing to the eye
    inline float GetManaPercent()
    {
        return (((float)m_creature->GetPower(POWER_MANA) / (float)m_creature->GetMaxPower(POWER_MANA)) * 100);
    }

    inline float GetVictimDistance()
    {
        return (m_creature->getVictim() ? m_creature->GetDistance2d(m_creature->getVictim()) : 999.9f);
    }

    void StopAttacking()
    {
        if (Unit* victim = m_creature->getVictim())
            m_creature->SendMeleeAttackStop(victim);

        if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE)
        {
            m_creature->GetMotionMaster()->Clear(false);
            m_creature->GetMotionMaster()->MoveIdle();
            m_creature->StopMoving();
        }
    }

    void StartAttacking()
    {
        if (Unit* victim = m_creature->getVictim())
            m_creature->SendMeleeAttackStart(victim);

        if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE)
        {
            m_creature->GetMotionMaster()->Clear(false);
            m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim(), 0.0f, 0.0f);
        }
    }
};

CreatureAI* GetAI_boss_arugal(Creature* pCreature)
{
    return new boss_arugalAI(pCreature);
}

/*######
## npc_arugal
######*/

enum
{
    SAY_INTRO_1             = -1033009,
    SAY_INTRO_2             = -1033010,
    SAY_INTRO_3             = -1033011,
    SAY_INTRO_4             = -1033012,

    SPELL_SPAWN             = 7741,

    NPC_VINCENT             = 4444
};

struct MANGOS_DLL_DECL npc_arugalAI : public ScriptedAI
{
    npc_arugalAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    uint32 m_uiSpeechTimer;
    uint8 m_uiSpeechStep;
    ScriptedInstance* m_pInstance;

    void Reset()
    {
        m_uiSpeechTimer = 0;
        m_uiSpeechStep = 0;

        m_creature->SetVisibility(VISIBILITY_OFF);

        if (m_pInstance && m_pInstance->GetData(TYPE_INTRO) == NOT_STARTED)
            m_uiSpeechStep = 1;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_uiSpeechStep)
            return;

        if (m_uiSpeechTimer < uiDiff)
        {
            switch(m_uiSpeechStep)
            {
                case 1:
                    m_creature->SetVisibility(VISIBILITY_ON);
                    m_uiSpeechTimer = 500;
                    break;
                case 2:
                    DoCastSpellIfCan(m_creature, SPELL_SPAWN);
                    m_uiSpeechTimer = 2000;
                    break;
                case 3:
                    //make him die
                    if (Creature* pVincent = GetClosestCreatureWithEntry(m_creature,NPC_VINCENT,20.0f))
                        pVincent->SetStandState(UNIT_STAND_STATE_DEAD);

                    m_uiSpeechTimer = 10000;
                    break;
                case 4:
                    DoScriptText(SAY_INTRO_1, m_creature);
                    //m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                    m_uiSpeechTimer = 1750;
                    break;
                case 5:
                    m_creature->HandleEmote(EMOTE_ONESHOT_POINT);
                    m_uiSpeechTimer = 1750;
                    break;
                case 6:
                    DoScriptText(SAY_INTRO_2, m_creature);
                    m_uiSpeechTimer = 1750;
                    break;
                case 7:
                    m_creature->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                    m_uiSpeechTimer = 1750;
                    break;
                case 8:
                    //m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                    DoScriptText(SAY_INTRO_3, m_creature);
                    m_uiSpeechTimer = 1750;
                    break;
                case 9:
                    m_creature->HandleEmote(EMOTE_ONESHOT_LAUGH);
                    m_uiSpeechTimer = 1750;
                    break;
                case 10:
                    DoScriptText(SAY_INTRO_4, m_creature);
                    m_uiSpeechTimer = 2000;
                    break;
                case 11:
                    DoCastSpellIfCan(m_creature, SPELL_SPAWN);
                    m_uiSpeechTimer = 500;
                    break;
                case 12:
                    if (m_pInstance)
                        m_pInstance->SetData(TYPE_INTRO,DONE);

                    m_creature->SetVisibility(VISIBILITY_OFF);
                    m_uiSpeechStep = 0;
                    return;
                default:
                    m_uiSpeechStep = 0;
                    return;
            }
            ++m_uiSpeechStep;
        }
        else
            m_uiSpeechTimer -= uiDiff;
    }

    void AttackStart(Unit* /*who*/) { }
};

CreatureAI* GetAI_npc_arugal(Creature* pCreature)
{
    return new npc_arugalAI(pCreature);
}

/*######
## npc_deathstalker_vincent
######*/

enum
{
    SAY_VINCENT_DIE     = -1033016,

    FACTION_FRIENDLY    = 35
};

struct MANGOS_DLL_DECL npc_deathstalker_vincentAI : public ScriptedAI
{
    npc_deathstalker_vincentAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_INTRO) == DONE && !m_creature->GetByteValue(UNIT_FIELD_BYTES_1, 0))
            m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (pDoneBy)
        {
            m_creature->SetInCombatWith(pDoneBy);
            pDoneBy->SetInCombatWith(m_creature);
        }

        if (m_creature->getStandState())
            m_creature->SetStandState(UNIT_STAND_STATE_STAND);

        if (uiDamage >= m_creature->GetHealth())
        {
            m_creature->GetHealth() > 1 ? uiDamage = m_creature->GetHealth() - 1 : uiDamage = 0;
            m_creature->setFaction(FACTION_FRIENDLY);
            EnterEvadeMode();
            DoScriptText(SAY_VINCENT_DIE, m_creature);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_creature->isInCombat() && m_creature->getFaction() == FACTION_FRIENDLY)
            EnterEvadeMode();

        ScriptedAI::UpdateAI(uiDiff);
    }

    void EnterEvadeMode()
    {
        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop(true);
        m_creature->LoadCreatureAddon();

        m_creature->SetLootRecipient(NULL);

        Reset();
    }
};

CreatureAI* GetAI_npc_deathstalker_vincent(Creature* pCreature)
{
    return new npc_deathstalker_vincentAI(pCreature);
}

void AddSC_shadowfang_keep()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_shadowfang_prisoner";
    newscript->pGossipHello =  &GossipHello_npc_shadowfang_prisoner;
    newscript->pGossipSelect = &GossipSelect_npc_shadowfang_prisoner;
    newscript->GetAI = &GetAI_npc_shadowfang_prisoner;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_arugal_voidwalker";
    newscript->GetAI = &GetAI_mob_arugal_voidwalker;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_arugal";
    newscript->GetAI = &GetAI_npc_arugal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_arugal";
    newscript->GetAI = &GetAI_boss_arugal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_deathstalker_vincent";
    newscript->GetAI = &GetAI_npc_deathstalker_vincent;
    newscript->RegisterSelf();
}
