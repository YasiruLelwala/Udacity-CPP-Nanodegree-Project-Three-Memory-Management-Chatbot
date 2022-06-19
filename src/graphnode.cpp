#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge) // coming as a copy so taking transferring ownership here
                                                                        // it should be passed with std::move 
{
    _childEdges.push_back(std::move(edge)); //using push_back(x) would create a copy of the object, while push_back(move(x)) would tell push_back() that it may "steal" the contents of x, leaving x in an unusable and undefined state.
}


void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
   _chatBot = std::move(chatbot);
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(std::move(_chatBot));
}


GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    return _childEdges[index].get();    
}