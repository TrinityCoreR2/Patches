/*
 * Copyright (C) 2015-2016 TrinityCore R2
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "InstanceSaveMgr.h"
#include "InstanceScript.h"
#include "MapManager.h"

class npc_change : public CreatureScript
{
    public:
        npc_change() : CreatureScript("npc_change") { }

         bool OnGossipHello(Player *player, Creature *_creature)
           {
  	        if (player->isInCombat()) 
                {		
				     /// @todo check Combat
                    _creature->MonsterWhisper("You are in Combat", player->GetGUID());
				    player->CLOSE_GOSSIP_MENU();
					return true;
                }
                else
                { 
				    player->ADD_GOSSIP_ITEM( 0, "10 Марок - Сбросить КД Подземелий"                                    , GOSSIP_SENDER_MAIN, 1);
				    player->ADD_GOSSIP_ITEM( 0, "10 Марок - 25 Очков Арены"                                   , GOSSIP_SENDER_MAIN, 2);
				    player->ADD_GOSSIP_ITEM( 0, "10 Знаков Справедливости - 1 Марка"                                             , GOSSIP_SENDER_MAIN, 3);
				    player->ADD_GOSSIP_ITEM( 0, "2 Марки - 1 Эмблема Триумфа"                                              , GOSSIP_SENDER_MAIN, 4);
				    player->ADD_GOSSIP_ITEM( 0, "4 Марки - 5000 Очков Чести"                                         , GOSSIP_SENDER_MAIN, 5);
				    player->ADD_GOSSIP_ITEM( 0, "1 Марка - 10 Знаков Справедливости"                                             , GOSSIP_SENDER_MAIN, 6);
				    player->ADD_GOSSIP_ITEM( 0, "1 Марка - 10 Простой Древесины"                                   , GOSSIP_SENDER_MAIN, 7);
				    player->ADD_GOSSIP_ITEM( 0, "1 Марка - 1 Металлолом"                                   , GOSSIP_SENDER_MAIN, 7);
				    player->ADD_GOSSIP_ITEM( 0, "100 Марок - Поводья повелителя воронов"                   , GOSSIP_SENDER_MAIN, 16);
				    player->ADD_GOSSIP_ITEM( 0, "50 Марок - Стремительная жевра"                               , GOSSIP_SENDER_MAIN, 17);
				    player->ADD_GOSSIP_ITEM( 0, "75 Марок - Стремительный зульский тигр"                         , GOSSIP_SENDER_MAIN, 18);
		        }	


				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());         
			    return true;
            }

            bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
            {

                if (sender != GOSSIP_SENDER_MAIN)
				    return true;

                player->PlayerTalkClass->ClearMenus();

                switch(uiAction)
                {

                    case 1:
					    if (player->HasItemCount(19322, 10, true))
						{
							player->DestroyItemCount(19322, 10, true);
							// Unbind ALL instances
							for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
							{
								Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
								for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
								{
									InstanceSave* save = itr->second.save;
									if (itr->first != player->GetMapId())
										player->UnbindInstance(itr, Difficulty(i));
									else
										++itr;
								}
							}
							_creature->MonsterWhisper("Все подземелья сброшены!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();
						}
						else
						{
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();
						}
                        break;
 
                    case 2:
					    if (player->HasItemCount(19322, 10, true))
						{

							player->DestroyItemCount(19322, 10, true);								
							player->ModifyArenaPoints(+25);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

						}
						else
						{
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();									
						}
                        break;


                    case 3:
					    if (player->HasItemCount(29434, 10, true))
						{
						    player->DestroyItemCount(29434, 10, true);								
							player->AddItem(19322, 1);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

						}
						else
						{									
							_creature->MonsterWhisper("Не хватает Знаков Справедливости!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();
						}
                        break;

                    case 4:
					    if (player->HasItemCount(19322, 2, true))
						{

							player->DestroyItemCount(19322, 2, true);								
							player->AddItem(47241, 1);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{									
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();
					    }
                        break;

                    case 5:
					    if (player->HasItemCount(19322, 4, true))
						{

							player->ModifyHonorPoints(+5000);							
							player->DestroyItemCount(19322, 4, true);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
                    case 6:
					    if (player->HasItemCount(19322, 1, true))
						{
						    player->AddItem(29434, 10);
							player->DestroyItemCount(19322, 1, true);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
                    case 7: // Wood 
					    if (player->HasItemCount(19322, 1, true))
						{
						    player->AddItem(4470, 10);
							player->DestroyItemCount(19322, 1, true);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
                    case 8: // Metal
					    if (player->HasItemCount(19322, 1, true))
						{
						    player->AddItem(35691, 1);
							player->DestroyItemCount(19322, 1, true);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
						
						
						
						
						
				    case 16: // Raven Lord Mount
					    if (player->HasItemCount(19322, 100, true))
						{
						    player->AddItem(32768, 1);
							player->DestroyItemCount(19322, 100, true);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
				    case 17: // Swift Zhevra Mount
					    if (player->HasItemCount(19322, 50, true))
						{
						    player->AddItem(37719, 1);
							player->DestroyItemCount(19322, 50, true);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
				    case 18: // Swift Zulian tiger Mount
					    if (player->HasItemCount(19322, 75, true))
						{
						    player->AddItem(19902, 1);
							player->DestroyItemCount(19322, 75, true);
							_creature->MonsterWhisper("Успешный обмен!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Нехватает Марки!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
                    default:
                        break;
                }
                return true;
        }
};

void AddSC_npc_change()
{
    new npc_change();
}
