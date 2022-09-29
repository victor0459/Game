#include"player_manager.h"
pthread_mutex_t playerManager::players_mutex=PTHREAD_MUTEX_INITIALIZER;
players playerManager::m_players;
