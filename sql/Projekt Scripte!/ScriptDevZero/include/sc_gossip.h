/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef SC_GOSSIP_H
#define SC_GOSSIP_H

#include "Player.h"
#include "GossipDef.h"
#include "QuestDef.h"

// Gossip Item Text
#define GOSSIP_TEXT_BROWSE_GOODS        "Ich sehe mich hier nur mal um"
#define GOSSIP_TEXT_TRAIN               "Ich benötige eine Ausbildung"

#define GOSSIP_TEXT_BANK                "Die Bank"
#define GOSSIP_TEXT_IRONFORGE_BANK      "Die Bank von Eisenschmiede"
#define GOSSIP_TEXT_STORMWIND_BANK      "Die Bank von Sturmwind"
#define GOSSIP_TEXT_WINDRIDER           "Der Windreitermeister"
#define GOSSIP_TEXT_GRYPHON             "Der Greifenmeister"
#define GOSSIP_TEXT_BATHANDLER          "Der Fledermausführer"
#define GOSSIP_TEXT_HIPPOGRYPH          "Der Hippogryphenmeister"
#define GOSSIP_TEXT_ZEPPLINMASTER       "Zeppelinmeister"
#define GOSSIP_TEXT_DEEPRUNTRAM         "Die Tiefenbahn"
#define GOSSIP_TEXT_FERRY               "Fähre von Rut'theran"
#define GOSSIP_TEXT_FLIGHTMASTER        "Den Flugmeister"
#define GOSSIP_TEXT_AUCTIONHOUSE        "Das Auktionshaus"
#define GOSSIP_TEXT_GUILDMASTER         "Der Gildenmeister"
#define GOSSIP_TEXT_INN                 "Ein Gasthaus"
#define GOSSIP_TEXT_MAILBOX             "Ein Briefkasten"
#define GOSSIP_TEXT_STABLEMASTER        "Der Stallmeister"
#define GOSSIP_TEXT_WEAPONMASTER        "Der Waffenlehrer"
#define GOSSIP_TEXT_OFFICERS            "Die Offiziersmesse"
#define GOSSIP_TEXT_BATTLEMASTER        "Kampfmeister"
#define GOSSIP_TEXT_BARBER              "Barbier"
#define GOSSIP_TEXT_CLASSTRAINER        "Ein Lehrer für eine Klasse"
#define GOSSIP_TEXT_PROFTRAINER         "Ein Lehrer für einen Beruf"
#define GOSSIP_TEXT_LEXICON             "Lexikon der Macht"

#define GOSSIP_TEXT_ALTERACVALLEY       "Das Alteractal"
#define GOSSIP_TEXT_ARATHIBASIN         "Das Arathibecken"
#define GOSSIP_TEXT_WARSONGULCH         "Die Kriegshymnem Schlucht"

#define GOSSIP_TEXT_DRUID               "Druide"
#define GOSSIP_TEXT_HUNTER              "Jäger"
#define GOSSIP_TEXT_PRIEST              "Priester"
#define GOSSIP_TEXT_ROGUE               "Schurke"
#define GOSSIP_TEXT_WARRIOR             "Krieger"
#define GOSSIP_TEXT_PALADIN             "Paladin"
#define GOSSIP_TEXT_SHAMAN              "Schamane"
#define GOSSIP_TEXT_MAGE                "Magier"
#define GOSSIP_TEXT_WARLOCK             "Hexenmeister"

#define GOSSIP_TEXT_ALCHEMY             "Alchemie"
#define GOSSIP_TEXT_BLACKSMITHING       "Schmiedekunst"
#define GOSSIP_TEXT_COOKING             "Kochkunst"
#define GOSSIP_TEXT_ENCHANTING          "Verzauberkunst"
#define GOSSIP_TEXT_ENGINEERING         "Ingenieurskunst"
#define GOSSIP_TEXT_FIRSTAID            "Erste Hilfe"
#define GOSSIP_TEXT_HERBALISM           "Kräuterkunde"
#define GOSSIP_TEXT_LEATHERWORKING      "Lederverarbeitung"
#define GOSSIP_TEXT_TAILORING           "Schneiderei"
#define GOSSIP_TEXT_MINING              "Bergbau"
#define GOSSIP_TEXT_FISHING             "Angeln"
#define GOSSIP_TEXT_SKINNING            "Kürschnerei"
#define GOSSIP_TEXT_JEWELCRAFTING       "Juwelenschleifen"
#define GOSSIP_TEXT_INSCRIPTION         "Inschriftenkunde"


enum
{
    // Skill defines
    TRADESKILL_ALCHEMY             = 1,
    TRADESKILL_BLACKSMITHING       = 2,
    TRADESKILL_COOKING             = 3,
    TRADESKILL_ENCHANTING          = 4,
    TRADESKILL_ENGINEERING         = 5,
    TRADESKILL_FIRSTAID            = 6,
    TRADESKILL_HERBALISM           = 7,
    TRADESKILL_LEATHERWORKING      = 8,
    TRADESKILL_POISONS             = 9,
    TRADESKILL_TAILORING           = 10,
    TRADESKILL_MINING              = 11,
    TRADESKILL_FISHING             = 12,
    TRADESKILL_SKINNING            = 13,

    TRADESKILL_LEVEL_NONE          = 0,
    TRADESKILL_LEVEL_APPRENTICE    = 1,
    TRADESKILL_LEVEL_JOURNEYMAN    = 2,
    TRADESKILL_LEVEL_EXPERT        = 3,
    TRADESKILL_LEVEL_ARTISAN       = 4,
    TRADESKILL_LEVEL_MASTER        = 5,

    // Gossip defines
    GOSSIP_ACTION_TRADE            = 1,
    GOSSIP_ACTION_TRAIN            = 2,
    GOSSIP_ACTION_TAXI             = 3,
    GOSSIP_ACTION_GUILD            = 4,
    GOSSIP_ACTION_BATTLE           = 5,
    GOSSIP_ACTION_BANK             = 6,
    GOSSIP_ACTION_INN              = 7,
    GOSSIP_ACTION_HEAL             = 8,
    GOSSIP_ACTION_TABARD           = 9,
    GOSSIP_ACTION_AUCTION          = 10,
    GOSSIP_ACTION_INN_INFO         = 11,
    GOSSIP_ACTION_UNLEARN          = 12,
    GOSSIP_ACTION_INFO_DEF         = 1000,

    GOSSIP_SENDER_MAIN             = 1,
    GOSSIP_SENDER_INN_INFO         = 2,
    GOSSIP_SENDER_INFO             = 3,
    GOSSIP_SENDER_SEC_PROFTRAIN    = 4,
    GOSSIP_SENDER_SEC_CLASSTRAIN   = 5,
    GOSSIP_SENDER_SEC_BATTLEINFO   = 6,
    GOSSIP_SENDER_SEC_BANK         = 7,
    GOSSIP_SENDER_SEC_INN          = 8,
    GOSSIP_SENDER_SEC_MAILBOX      = 9,
    GOSSIP_SENDER_SEC_STABLEMASTER = 10
};

extern uint32 GetSkillLevel(Player* pPlayer,uint32 skill);

// Defined fuctions to use with player.

// This fuction add's a menu item,
// Icon Id
// Text
// Sender(this is to identify the current Menu with this item)
// Option id (identifies this Menu Item)
// Text to be displayed in pop up box
// Coded
#define ADD_GOSSIP_ITEM(uiIcon, chrText, uiSender, uiOptionId)   PlayerTalkClass->GetGossipMenu().AddMenuItem(uiIcon, chrText, uiSender, uiOptionId, "")
#define ADD_GOSSIP_ITEM_ID(uiIcon, iTextId, uiSender, uiOptionId)   PlayerTalkClass->GetGossipMenu().AddMenuItem(uiIcon, iTextId, uiSender, uiOptionId, 0)
#define ADD_GOSSIP_ITEM_EXTENDED(uiIcon, chrText, uiSender, uiOptionId, chrBoxMessage, bCode)   PlayerTalkClass->GetGossipMenu().AddMenuItem(uiIcon, chrText, uiSender, uiOptionId, chrBoxMessage, bCode)

// This fuction Sends the current menu to show to client, uiTextId - NPCTEXTID(uint32) , uiGuid - npc guid(uint64)
#define SEND_GOSSIP_MENU(uiTextId, uiGuid)      PlayerTalkClass->SendGossipMenu(uiTextId, uiGuid)

// This fuction shows POI(point of interest) to client.
// a - position X
// b - position Y
// c - Icon Id
// d - Flags
// e - Data
// f - Location Name
#define SEND_POI(a, b, c, d, e, f)      PlayerTalkClass->SendPointOfInterest(a, b, c, d, e, f)

// Closes the Menu
#define CLOSE_GOSSIP_MENU()        PlayerTalkClass->CloseGossip()

// Fuction to tell to client the details
// a - quest object
// b - npc guid(uint64)
// c - Activate accept(bool)
#define SEND_QUEST_DETAILS(a, b, c)  PlayerTalkClass->SendQuestDetails(a, b, c)

// Fuction to tell to client the requested items to complete quest
// a - quest object
// b - npc guid(uint64)
// c - Iscompletable(bool)
// d - close at cancel(bool) - in case single incomplite ques
#define SEND_REQUESTEDITEMS(a, b, c, d) PlayerTalkClass->SendRequestedItems(a, b, c, d)

// Fuctions to send NPC lists, a - is always the npc guid(uint64)
#define SEND_VENDORLIST(a)         GetSession()->SendListInventory(a)
#define SEND_TRAINERLIST(a)        GetSession()->SendTrainerList(a)
#define SEND_BANKERLIST(a)         GetSession()->SendShowBank(a)
#define SEND_TABARDLIST(a)         GetSession()->SendTabardVendorActivate(a)
#define SEND_TAXILIST(a)           GetSession()->SendTaxiStatus(a)

// Function to send the Auction List, a - npc guid(uint64), b - pointer to npc(Creature*)
#define SEND_AUCTIONLIST(a, b)     GetSession()->SendAuctionHello(a, b)

// Ressurect's the player if is dead.
#define SEND_SPRESURRECT()         GetSession()->SendSpiritResurrect()

// Get the player's honor rank.
#define GET_HONORRANKINFO()            GetHonorRankInfo()
// -----------------------------------

// defined fuctions to use with Creature

#define QUEST_DIALOG_STATUS(a, b, c)   GetSession()->getDialogStatus(a, b, c)
#endif
