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
SDName: Moonglade
SD%Complete: 100
SDComment: Quest support: 30, 272, 5929, 5930. Special Flight Paths for Druid class.
SDCategory: Moonglade
EndScriptData */

/* ContentData
npc_bunthen_plainswind
npc_great_bear_spirit
npc_silva_filnaveth
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"
#include "ObjectMgr.h"

/*######
## npc_bunthen_plainswind
######*/

enum
{
    QUEST_SEA_LION_HORDE   = 30,
    QUEST_SEA_LION_ALLY    = 272,
    TAXI_PATH_ID_ALLY      = 315,
    TAXI_PATH_ID_HORDE     = 316
};

#define GOSSIP_ITEM_THUNDER     "Ich w�rde gerne nach Donnerfels fliegen."
#define GOSSIP_ITEM_AQ_END      "Kannst du mir sagen, wo sich Halber Anh�nger der Wasserbelastbarkeit befindet?"

bool GossipHello_npc_bunthen_plainswind(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->getClass() != CLASS_DRUID)
        pPlayer->SEND_GOSSIP_MENU(4916, pCreature->GetGUID());
    else if (pPlayer->GetTeam() != HORDE)
    {
        if (pPlayer->GetQuestStatus(QUEST_SEA_LION_ALLY) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AQ_END, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        pPlayer->SEND_GOSSIP_MENU(4917, pCreature->GetGUID());
    }
    else if (pPlayer->getClass() == CLASS_DRUID && pPlayer->GetTeam() == HORDE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THUNDER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if (pPlayer->GetQuestStatus(QUEST_SEA_LION_HORDE) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AQ_END, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        pPlayer->SEND_GOSSIP_MENU(4918, pCreature->GetGUID());
    }
    return true;
}

bool GossipSelect_npc_bunthen_plainswind(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->CLOSE_GOSSIP_MENU();

            if (pPlayer->getClass() == CLASS_DRUID && pPlayer->GetTeam() == HORDE)
                pPlayer->ActivateTaxiPathTo(TAXI_PATH_ID_HORDE);

            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->SEND_GOSSIP_MENU(5373, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->SEND_GOSSIP_MENU(5376, pCreature->GetGUID());
            break;
    }
    return true;
}

/*######
## npc_great_bear_spirit
######*/

#define GOSSIP_BEAR1 "Was repr�sentierst du, Geist?"
#define GOSSIP_BEAR2 "Ich suche nach der Wichtigkeit der St�rke des K�rpers."
#define GOSSIP_BEAR3 "Ich suche nach der Wichtigkeit der St�rke des Herzes."
#define GOSSIP_BEAR4 "Ich habe eure Worte geh�hrt, gro�er B�rengeist, und ich verstehe sie. Ich werde jetzt nach deiner Weisheit suchen, um die Weise des Greifers zu erlernen."

bool GossipHello_npc_great_bear_spirit(Player* pPlayer, Creature* pCreature)
{
    //ally or horde quest
    if (pPlayer->GetQuestStatus(5929) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(5930) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        pPlayer->SEND_GOSSIP_MENU(4719, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(4718, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_great_bear_spirit(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(4721, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(4733, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(4734, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->SEND_GOSSIP_MENU(4735, pCreature->GetGUID());
            if (pPlayer->GetQuestStatus(5929)==QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(5929);
            if (pPlayer->GetQuestStatus(5930)==QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(5930);
            break;
    }
    return true;
}

/*######
## npc_silva_filnaveth
######*/

#define GOSSIP_ITEM_RUTHERAN    "K�nntet ihr mich nach Rut'theran fliegen."
#define GOSSIP_ITEM_AQ_AGI      "Kannst du mir sagen, wo sich Halber Anh�nger der Wasserbelastbarkeit befindet?"

bool GossipHello_npc_silva_filnaveth(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->getClass() != CLASS_DRUID)
        pPlayer->SEND_GOSSIP_MENU(4913, pCreature->GetGUID());
    else if (pPlayer->GetTeam() != ALLIANCE)
    {
        if (pPlayer->GetQuestStatus(QUEST_SEA_LION_HORDE) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AQ_AGI, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        pPlayer->SEND_GOSSIP_MENU(4915, pCreature->GetGUID());
    }
    else if (pPlayer->getClass() == CLASS_DRUID && pPlayer->GetTeam() == ALLIANCE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTHERAN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if (pPlayer->GetQuestStatus(QUEST_SEA_LION_ALLY) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AQ_AGI, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        pPlayer->SEND_GOSSIP_MENU(4914, pCreature->GetGUID());
    }
    return true;
}

bool GossipSelect_npc_silva_filnaveth(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->CLOSE_GOSSIP_MENU();

            if (pPlayer->getClass() == CLASS_DRUID && pPlayer->GetTeam() == ALLIANCE)
                pPlayer->ActivateTaxiPathTo(TAXI_PATH_ID_ALLY);

            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->SEND_GOSSIP_MENU(5374, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->SEND_GOSSIP_MENU(5375, pCreature->GetGUID());
            break;
    }
    return true;
}

void AddSC_moonglade()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_bunthen_plainswind";
    pNewScript->pGossipHello = &GossipHello_npc_bunthen_plainswind;
    pNewScript->pGossipSelect = &GossipSelect_npc_bunthen_plainswind;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_great_bear_spirit";
    pNewScript->pGossipHello = &GossipHello_npc_great_bear_spirit;
    pNewScript->pGossipSelect = &GossipSelect_npc_great_bear_spirit;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_silva_filnaveth";
    pNewScript->pGossipHello = &GossipHello_npc_silva_filnaveth;
    pNewScript->pGossipSelect = &GossipSelect_npc_silva_filnaveth;
    pNewScript->RegisterSelf();
}
