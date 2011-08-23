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
SDName: Uldaman
SD%Complete: 100
SDComment: Quest support: 2278
SDCategory: Uldaman
EndScriptData */

/* ContentData
npc_lore_keeper_of_norgannon
EndContentData */

#include "precompiled.h"
#include "uldaman.h"

/*######
## npc_lore_keeper_of_norgannon
######*/

bool GossipHello_npc_lore_keeper_of_norgannon(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(2278) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wer sind die Irdenen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(1079, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_lore_keeper_of_norgannon(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Was ist eine \"Matrix für unterirdische Lebewesen\"?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(1080, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Von welchen Anomalien sprecht Ihr?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(1081, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Was ist \"ureigenstes widerstandsfähiges Material\"?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            pPlayer->SEND_GOSSIP_MENU(1082, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Also bestanden die Irdenen aus Stein?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            pPlayer->SEND_GOSSIP_MENU(1083, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Was sollte ich noch über die Irdenen wissen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            pPlayer->SEND_GOSSIP_MENU(1084, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich glaube, ich verstehe, warum die Schöpfer die Irdenen erschaffen haben. Von welchen Anomalien der Irdenen war zuvor die Rede?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
            pPlayer->SEND_GOSSIP_MENU(1085, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Durch welchen hohen Druck würden sich die Irdenen destabilisieren?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
            pPlayer->SEND_GOSSIP_MENU(1086, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Was passiert, wenn sich die Irdenen destabilisieren?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
            pPlayer->SEND_GOSSIP_MENU(1087, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+9:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Troggs?! Sind das die gleichen Troggs, wie wir sie heute kennen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
            pPlayer->SEND_GOSSIP_MENU(1088, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+10:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ihr erwähntet zwei Resultate, wenn sich die Irdenen destabilisieren. Welches ist das zweite?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
            pPlayer->SEND_GOSSIP_MENU(1089, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+11:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zwerge! Ihr wollt mir also sagen, dass die Zwerge von den Irdenen abstammen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12);
            pPlayer->SEND_GOSSIP_MENU(1090, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+12:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Und wir reden hier von den Zwergen, wie wir sie heute kennen, ja? Gibt es denn noch andere Verbindungen der Zwerge zu den Irdenen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
            pPlayer->SEND_GOSSIP_MENU(1091, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+13:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wer sind die Schöpfer?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14);
            pPlayer->SEND_GOSSIP_MENU(1092, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+14:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Darüber muss ich jetzt erst mal nachdenken.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
            pPlayer->SEND_GOSSIP_MENU(1093, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+15:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich greif jetzt auf die Scheiben zu.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+16);
            pPlayer->SEND_GOSSIP_MENU(1094, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+16:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->AreaExploredOrEventHappens(2278);
            break;
    }
    return true;
}

void AddSC_uldaman()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_lore_keeper_of_norgannon";
    pNewScript->pGossipHello = &GossipHello_npc_lore_keeper_of_norgannon;
    pNewScript->pGossipSelect = &GossipSelect_npc_lore_keeper_of_norgannon;
    pNewScript->RegisterSelf();
}
