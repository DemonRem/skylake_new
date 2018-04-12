#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#define SERVER_ID 2017 //[0xe107]

#define	SERVER_MAX_PLAYERS  4096 
#define	SERVER_MAX_CREATURES //8192 

#define	SERVER_DEFAULT_PORT  2017
#define SERVER_INTERNAL_COMUNICATION_BUFFER_SIZE 512

//WORLD SERVER------------------------------
#define RECV_HEAD 0
#define RECV_BODY 1


#define SERVER_START_NORMAL 0
#define SERVER_START_MAP_DEF 1
#define SERVER_START_TEST 2

#define SERVER_WORLD_LISTENING_PORT 7788
#define SERVER_WORKER_THREADS 2
#define SERVER_TASK_COUNT 1024 //128 lines of cache
#define SERVER_TIMER_TASK_COUNT 1024 //128 lines of cache
#define SERVER_CLUSTER_TASK_COUNT 32768 //MUST BE A POWER OF 2
#define SERVER_RECEIVE_BUFFER_SIZE  1024 // 6 lines of cache
#define SERVER_WORLD_MANAGER_MAX_NODES 25
#define SERVER_WORLD_WORKING_THREADS_MAX 2

//ARBITER SERVER------------------------------
#define SC_PLAYER_NAME_MAX_LENGTH  40
#define SC_PLAYER_MAX_CHARACTER_COUNT  6
#define SC_PLAYER_DETAILS_1_BUFFER_SIZE  32
#define SC_PLAYER_DETAILS_2_BUFFER_SIZE  64
#define SC_PLAYER_DETAILS_3_BUFFER_SIZE  8

#define SC_CHAT_MESSAGE_MAX_LENGTH  512
#define SC_CHAT_MAX_MESSAGE_LENGTH  270
#define SC_INVENTORY_MAX_SLOTS  104 //8 * 13
#define SC_INVENTORY_MIN_SLOTS  32 //8 * 4
#define SC_INVENTORY_PROFILE_SLOTS_COUNT  21
#define SC_WORKER_THREADS_COUNT  2
#define SC_RECEIVE_BUFFER_SIZE 8196



#endif