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
SDName: Winterspring
SD%Complete: 90
SDComment: Quest support: 5126 (Loraxs' tale missing proper gossip items text). Vendor Rivern Frostwind. Obtain Cache of Mau'ari
SDCategory: Winterspring
EndScriptData */

/* ContentData
npc_lorax
npc_rivern_frostwind
npc_witch_doctor_mauari
EndContentData */

#include "precompiled.h"

/*######
## npc_lorax
######*/

bool GossipHello_npc_lorax(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(5126) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ihr m�sst schon entschuldigen, Lorax. Verr�cktisch sprech ich nicht.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_lorax(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Vergebt mir - ich wusste nicht, dass Ihr versteht, was ich sage. Was genau macht Ihr hier drau�en?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(3759, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ach ja? Vielleicht solltet Ihr mir sagen, was Euch bedr�ckt.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(3760, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Was f�r eine Vereinbarung?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(3761, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wie hat er denn die Vereinbarung gebrochen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(3762, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Vielleicht kann ich Euch ja behilflich sein. Ich schlage Euch einen Handel vor, Satyr: Ich beschaffe Euch diese ungeschmiedete Brustplatte und t�te die Bestie, Goraluk Hammerbruch. Und im Gegenzug lehrt Ihr mich wie man die Brustplatte herstellt.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(3763, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->AreaExploredOrEventHappens(5126);
            break;
    }
    return true;
}

/*######
## npc_rivern_frostwind
######*/

bool GossipHello_npc_rivern_frostwind(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->isVendor() && pPlayer->GetReputationRank(589) == REP_EXALTED)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_rivern_frostwind(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetGUID());

    return true;
}

/*######
## npc_witch_doctor_mauari
######*/

bool GossipHello_npc_witch_doctor_mauari(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestRewardStatus(975))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich habe den Beh�lter von Mau'ri verloren. Was kann ich tun?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(3377, pCreature->GetGUID());
    }else
        pPlayer->SEND_GOSSIP_MENU(3375, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_witch_doctor_mauari(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction==GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->CastSpell(pPlayer, 16351, false);
    }

    return true;
}

void AddSC_winterspring()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_lorax";
    pNewScript->pGossipHello = &GossipHello_npc_lorax;
    pNewScript->pGossipSelect = &GossipSelect_npc_lorax;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_rivern_frostwind";
    pNewScript->pGossipHello = &GossipHello_npc_rivern_frostwind;
    pNewScript->pGossipSelect = &GossipSelect_npc_rivern_frostwind;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_witch_doctor_mauari";
    pNewScript->pGossipHello = &GossipHello_npc_witch_doctor_mauari;
    pNewScript->pGossipSelect = &GossipSelect_npc_witch_doctor_mauari;
    pNewScript->RegisterSelf();
}
