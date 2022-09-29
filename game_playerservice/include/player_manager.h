#pragma once
#include<stdio.h>
#include<ext/hash_map>
#include<pthread.h>
#include<unistd.h>
#include"player.h"
typedef __gnu_cxx::hash_map<int,player*> players;
typedef __gnu_cxx::hash_map<int,player*>::iterator players_it;

class playerManager{
	public:
		void player_add(int connfd,player*play){
			pthread_mutex_lock(&players_mutex);
			m_players[connfd]=play;
		
			pthread_mutex_unlock(&players_mutex);

		}
		void find_player(int connfd,player&p){
			players_it it=m_players.find(connfd);
			if(it==m_players.end()){
				return;
			}
			p=*m_players[connfd];
		}
		void player_del(int connfd){
			pthread_mutex_lock(&players_mutex);
			players_it it=m_players.find(connfd);
			if(it==m_players.end()){
				return;
			}
			m_players.erase(connfd);
			pthread_mutex_unlock(&players_mutex);
		}
	public:
	static players m_players;
	static pthread_mutex_t players_mutex;
};

