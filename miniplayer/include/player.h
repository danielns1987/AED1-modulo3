#ifndef PLAYER_H
#define PLAYER_H
typedef struct player t_player;
t_player *player_criar(void);
int player_reproduzir(t_player *p, t_musica *m);
int player_anterior(t_player *p);
int player_avancar(t_player *p);
t_musica *player_atual(const t_player *p);
void player_destruir(t_player *p);
#endif