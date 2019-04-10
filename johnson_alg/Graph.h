//
// Created by artyom on 08.04.19.
//

#ifndef JOHNSON_ALG_GRAPH_H
#define JOHNSON_ALG_GRAPH_H

#include <memory>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

#include "FH.h"

using std::priority_queue;
using std::unique_ptr;
using std::make_unique;
using std::vector;
using std::pair;
using std::make_pair;

#define INF 1000000

class D
{
public:

    D(pair <int ,int> c) : m_c(c)
    {

    }

    int getKey()
    {
        return m_c.first;
    }
    //first is id, second is path length
    pair <int , int> m_c;
};


template <typename T>
class Nodee {
public:
    Nodee (T edge) : m_edge{edge} {}
    T get_edge()
    {
        return m_edge;
    }

    T m_edge;
};

class Edge
{
public:
    Edge(){}

    Edge(int from, int to, int cost) :
    m_from{from}, m_to{to}, m_cost{cost} {}
    int m_cost, m_from, m_to;
};

template  <typename T>
class Graph
{
public:
    Graph(vector <vector <int>> matrix, vector <T> &vertices)
    {
        m_edges.resize(vertices.size());
        m_vertices.resize(vertices.size());
        m_adj_list.resize(vertices.size());

        for (int i = 0; i < vertices.size(); i++)
        {
            m_vertices[i] = make_unique<Nodee <T>>(vertices[i]);
        }

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                if (matrix[i][j] < INF)
                {
                    m_edges.emplace_back(i, j, matrix[i][j]);
                    m_adj_list[i].push_back(make_pair(j, matrix[i][j]));
                }
            }
        }

    }

    vector <int> ford_bellman(int source_id)
    {
        vector <int> ret(m_vertices.size(), INF);
        ret[source_id] = 0;

        for (int i = 0; i < m_vertices.size() - 1; i++)
        {
            for (Edge j : m_edges)
            {
                if (ret[j.m_to] > ret[j.m_from] + j.m_cost)
                {
                    ret[j.m_to] = ret[j.m_from] + j.m_cost;
                }
            }
        }

        for (Edge  e : m_edges)
        {
            if (ret[e.m_to] > ret[e.m_from] + e.m_cost)
            {
                vector <int> null_vec(0);
                return null_vec;
            }
        }
        return ret;
    }

    vector <int> dijkstra(int source_id)
    {
        vector <int> ret(m_vertices.size(), INF);
        ret[source_id] = 0;

        FH <D> q;
        q.insert(D(make_pair(source_id, 0)));

        while (q.m_count)
        {
            shared_ptr <Node <D>> item = q.extract_min();
            D true_item = item ->m_key;

            int cur_id = true_item.m_c.first;
            for (pair <int, int> i : m_adj_list[cur_id])
            {
                int neigh_id = i.first;
                int edge_cost = i.second;

                if (ret[neigh_id] > ret[cur_id] + edge_cost)
                {
                    ret[neigh_id] = ret[cur_id] + edge_cost;
                    q.insert(D(make_pair(neigh_id, ret[neigh_id])));
                }
            }
        }

        return ret;
    }

    vector <vector <int>> johnson()
    {
        m_vertices.push_back(nullptr);
        m_adj_list.push_back(vector <pair<int, int>>(0));
        int s_id = static_cast<int>(m_vertices.size() - 1);
        for (int i = 0; i < m_vertices.size() - 1; i++)
        {
            Edge e(s_id, i, 0);
            m_edges.push_back(e);
            m_adj_list[s_id].push_back(make_pair(i, 0));
        }

        vector <int> bellman_ret = ford_bellman(s_id);
        if (bellman_ret.empty())
        {
            return vector <vector <int>>(0);
        }

        m_vertices.pop_back();
        while (m_edges[s_id].m_from == m_vertices.size())
        {
            m_edges.pop_back();
            s_id--;
        }

        m_adj_list.pop_back();

        for (int i = 0; i < m_adj_list.size(); i++)
        {
            for (int j = 0; j < m_adj_list[i].size(); j++)
            {
                m_adj_list[i][j].second += bellman_ret[i] - bellman_ret[j];
            }
        }

        vector <vector <int>>result_matrix;

        for (int i = 0; i < s_id; i++)
        {
            result_matrix.push_back(dijkstra(i));
        }

        for (int i = 0; i < m_adj_list.size(); i++)
        {
            for (int j = 0; j < m_adj_list[i].size(); j++)
            {
                m_adj_list[i][j].second += (-bellman_ret[i] +bellman_ret[j]);
            }
        }

        for (int i = 0; i < result_matrix.size(); i++)
        {
            for (int j = 0; j < result_matrix.size(); j++)
            {
                result_matrix[i][j] += (-bellman_ret[i] +bellman_ret[j]);
            }
        }

        return result_matrix;
    }

private:

    pair <int, int> find_neghbour(int from_id, int to_id)
    {
        vector <pair <int, int>> vec = m_adj_list[from_id];
        for (auto i : vec)
        {
            if (i.first == to_id)
            {
                return i;
            }
        }
    }

    vector <Edge> m_edges;
    vector <unique_ptr <Nodee <T>>> m_vertices;
    vector <vector <pair <int, int>>> m_adj_list;
};

#endif //JOHNSON_ALG_GRAPH_H
