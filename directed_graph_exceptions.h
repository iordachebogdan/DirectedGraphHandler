//
// Created by Bogdan Iordache on 3/6/2018.
//

#ifndef DIRECTEDGRAPHHANDLER_DIRECTED_GRAPH_EXCEPTIONS_H
#define DIRECTEDGRAPHHANDLER_DIRECTED_GRAPH_EXCEPTIONS_H

#include <exception>

namespace dgraph {
    class bad_dgraph_config : public std::exception {
        virtual const char* what() const throw() {
            return "Error in directed graph configuration!";
        }
    };
}

#endif //DIRECTEDGRAPHHANDLER_DIRECTED_GRAPH_EXCEPTIONS_H
