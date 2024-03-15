#pragma once

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "GameObject.h"
#include "SDL_GameObject.h"
#include "ManageFont.h"
#include "ManageTexture.h"
#include "SpItem.h"

static SDL_Texture* blindTex(SDL_Renderer* renderer)
{
    SDL_Surface* screenSurface = SDL_CreateRGBSurface(0, 1020, 600, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenSurface->pixels, screenSurface->pitch);
    Uint32* pixels = static_cast<Uint32*>(screenSurface->pixels);
    int pixelCount = screenSurface->w * screenSurface->h;

    for (int i = 0; i < pixelCount; ++i)
    {
        Uint8* pixel = reinterpret_cast<Uint8*>(&pixels[i]);

        // Lấy giá trị RGBA của pixel
        Uint8 r, g, b, a;
        SDL_GetRGBA(pixels[i], screenSurface->format, &r, &g, &b, &a);

        // Giảm độ sáng (ví dụ giảm 50%)
        r = static_cast<Uint8>(r * 0.5);
        g = static_cast<Uint8>(g * 0.5);
        b = static_cast<Uint8>(b * 0.5);

        // Tạo giá trị RGBA mới
        pixels[i] = SDL_MapRGBA(screenSurface->format, r, g, b, a);
    }
    SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,screenSurface);
    SDL_FreeSurface(screenSurface);
    return tex;
}



static void bfs_map(std::vector<std::vector<int>> v, int t,std::map<std::pair<int,int>,int>&mp)
{
    std::vector<int> q;
    q.push_back(t);
    int n = v.size();
    std::vector<bool> visit(n, false);
    std::vector<int> par(n, 0);
    std::vector<bool> check(n, false);
    visit[t] = true;
    while (!q.empty())
    {
        int u = q[0];
        q.erase(q.begin());
        for (int i : v[u])
        {
            if (!visit[i])
            {
                visit[i] = true;
                q.push_back(i);
                par[i] = u;
                if (check[i] == false)
                {
                    std::vector<int> path;
                    for (int v = i; v != t; v = par[v])
                    {
                        path.push_back(v);
                    }
                    path.push_back(t);
                    reverse(path.begin(), path.end());
                    mp[ {t, i}] = path[1];
                    check[i] = true;
                }
            }
        }
    }
}


static bool Collission(GameObject* p1,GameObject* p2)
{
    int x1=static_cast<SDLGameObject*>(p1)->GetPos().GetX(),y1=static_cast<SDLGameObject*>(p1)->GetPos().GetY(),w1=static_cast<SDLGameObject*>(p1)->GetW(),h1=static_cast<SDLGameObject*>(p1)->GetH();
    int x2=static_cast<SDLGameObject*>(p2)->GetPos().GetX(),y2=static_cast<SDLGameObject*>(p2)->GetPos().GetY(),w2=static_cast<SDLGameObject*>(p2)->GetW(),h2=static_cast<SDLGameObject*>(p2)->GetH();
    if(x1>=x2+w2||x1+w1<=x2||y1+h1<=y2||y2+h2<=y1)return false;
    return true;
}

static int Pos_Map_1(int x,int y,int w,int h)
{
    if(x+w>450&&x<900&&y+h<=550)return 12;
    if(x+w>350&&x<550&&y+h<=650)return 11;
    if(x+w>350&&x<550&&y+h<=750)return 10;
    if(x+w>1000&&x<1335&&y+h<=700)return 5;
    if(x+w>1480&&x<1680&&y+h<=750)return 13;
    if(x+w>1790&&y+h<=850)return 14;
    if(x+w>1335&&x<1395&&y+h<=870)return 8;
    if(x+w>1395&&x<1455&&y+h<=930)return 9;
    if(x+w>1455&&x<1515&&y+h<=990)return 15;
    if(x+w>450&&x<650&&y+h<=850)return 7;
    if(x+w>750&&x<1000&&y+h<=950)return 4;
    if(x+w>650&&x<750&&y+h<=1050)return 3;
    if(x<500&&y+h<=1050)return 1;
    if(x+w>1515&&y+h<=1050)return 6;
    return 2;
}

static int Pos_Map_2(int x,int y,int w,int h)
{
    if(x+w>450&&x<1050&&y+h<=920)return 2;
    if(x+w>1840&&y+h<=650)return 6;
    if(x+w>1640&&x<1840&&y+h<=750)return 5;
    if(x+w>1440&&x<1640&&y+h<=850)return 4;
    if(x+w>1240&&x<1440&&y+h<=950)return 3;
    if(x<750&&y+h<=1050)return 1;
    return 7;
}

static std::string GetPartText(std::string tmp,int k)
{
    if(k>tmp.size())k=tmp.size();
    std::string n="";
    for(int i=0; i<k; i++)n+=tmp[i];
    return n;
}

static void drawOnBoard(std::string id,std::string text,SDL_Renderer* renderer)
{
    SDL_Texture* tex=ManageFont::GetInstance()->createTex(id,text, {0,0,0,255},renderer);
    int w;
    int h;
    SDL_QueryTexture(tex,NULL,NULL,&w,&h);
    SDL_Surface* sur=IMG_Load("Image/bogoc.png");
    SDL_Texture* tex2=SDL_CreateTextureFromSurface(renderer,sur);
    SDL_FreeSurface(sur);
    int x=(1020-w)/2-50;
    int y=300;
    SDL_Rect dst= {x,y,1020-2*x,150};
    SDL_RenderCopy(renderer,tex2,NULL,&dst);
    dst= {(1020-w)/2,350,w,h};
    SDL_RenderCopy(renderer,tex,NULL,&dst);
}

static bool checkItem(std::vector<GameObject*> item,std::string id)
{
    for(GameObject* i:item)if(static_cast<SpItem*>(i)->GetID()==id)return true;
    return false;
}
