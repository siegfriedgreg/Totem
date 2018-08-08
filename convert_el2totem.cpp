#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct EdgeT
{
    long long src, dest;
};

bool edge_compare(EdgeT a, EdgeT b)
{
    return (a.src < b.src);
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        cout << "Usage : ./convert <edge list file> <totem file> -d | -u " << endl;
        return 0;
    }

    std::vector<EdgeT> coo_edges;
    long long num_edges = 0;
    long long max_vertex = 0;

    ifstream coo_in;
    coo_in.open(argv[1]);
    while (!coo_in.eof())
    {
        EdgeT edge;
        coo_in >> edge.src >> edge.dest;
        if (coo_in.eof()) break;
        coo_edges.push_back(edge);
        num_edges ++;
        if (edge.src  > max_vertex) max_vertex = edge.src;
        if (edge.dest > max_vertex) max_vertex = edge.dest;
    }
    coo_in.close();
    cout << "Finished reading " << num_edges << " edges, max_vertex = " << max_vertex << endl;

    long long *vertex_marker = new long long[max_vertex+1];
    for (long long v=0; v<=max_vertex; v++)
        vertex_marker[v] = -1;
    for (auto it = coo_edges.begin(); it != coo_edges.end(); it++)
    {
        vertex_marker[(*it).src] = 1;
        vertex_marker[(*it).dest] = 1;
    }
    long long num_vertices = 0;
    for (long long v=0; v<=max_vertex; v++)
    {
        if (vertex_marker[v] != -1)
        {
            vertex_marker[v] = num_vertices;
            num_vertices ++;
        }
    }
    for (auto it = coo_edges.begin(); it != coo_edges.end(); it++)
    {
        (*it).src = vertex_marker[(*it).src];
        (*it).dest = vertex_marker[(*it).dest];
    }
    cout << "Finished vertex packing, num_vertices = " << num_vertices << endl;
    delete[] vertex_marker; vertex_marker = NULL;

    sort(coo_edges.begin(), coo_edges.begin() + num_edges, edge_compare);
    cout << "Finished sorting" << endl;

    ofstream totem_out;
    totem_out.open(argv[2]);
    totem_out << "#Nodes:" << num_vertices << endl;
    totem_out << "#Edges:" << num_edges << endl;
    if ( strcmp( argv[3], "-d" ) == 0 )
    {
    totem_out << "#Directed" << endl;
    } else {
        totem_out << "#Undirected" << endl;
    }
    for (auto it = coo_edges.begin(); it != coo_edges.end(); it++)
    {
        totem_out << (*it).src << " " << (*it).dest << endl;
    }
    totem_out.close();
    cout << "Finished writing" << endl;
    return 0;
}

