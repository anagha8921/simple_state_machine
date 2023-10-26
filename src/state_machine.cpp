#include <ncurses.h>
#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;
enum class State {
    IDLE,
    WORKING,
    FINISHED,
};

struct Transition {
    State from;
    State to;
};

const std::vector<Transition> transitions = {
    {State::IDLE, State::WORKING},
    {State::WORKING, State::FINISHED},
    {State::FINISHED, State::IDLE},
};

// class LCM_Master : public rclcpp::Node
// {}
int main(int argc, char* argv[]) {
    // Initialize ncurses
    initscr();
    cbreak();        // Line buffering disabled
    noecho();        // Do not echo input characters
    keypad(stdscr, TRUE); // Enable function keys (F1, F2, etc.)
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("state_machine_node");
    // auto node = std::make_shared<LCM_Master>();
    char ch; 
    Transition transition;   
    // Implement the state machine logic here
    State current_state = State::IDLE;
    State previous_state;
   

while (rclcpp::ok()) {
    
     //while ((ch = getch()) != 'q') {
        RCLCPP_INFO(node->get_logger(),"Press a key");
        
        int ch=getch();     
        std::cout << "\n\r";
        refresh();
        if (ch  == 'i'){
            //RCLCPP_INFO(node->get_logger(), "current_state %d",current_state);
            if(current_state==State::FINISHED)
            {
                previous_state=State::FINISHED;
                current_state = State::IDLE;
                // RCLCPP_INFO(node->get_logger(),"\t\t");               
                RCLCPP_INFO(node->get_logger(),"Transition successful from FINISHED->IDLE");     
                        
            }
            else{                
                RCLCPP_INFO(node->get_logger(),"You have requested for an invalid transition(i)!");           
            }
                       
        }
        else if (ch  == 'w')
        {
            //RCLCPP_INFO(node->get_logger(), "current_state %d",current_state);
             if(current_state==State::IDLE)
            {
                previous_state=State::IDLE;
                current_state = State::WORKING;              
                RCLCPP_INFO(node->get_logger(),"Transition successful from IDLE->WORKING");
 
            }
            else{
               
                RCLCPP_INFO(node->get_logger(),"You have requested for an invalid transition(w)!");            
            }
            
        }
        else if (ch  == 'f')
        {
            //RCLCPP_INFO(node->get_logger(), "current_state %d",current_state);
             if(current_state==State::WORKING)
            {
                previous_state=State::WORKING;
                current_state = State::FINISHED;              
                RCLCPP_INFO(node->get_logger(),"Transition successful from WORKING->FINISHED");
            }
            else{                
                RCLCPP_INFO(node->get_logger(),"You have requested for an invalid transition(f)!");               
            }
              
        }
        else{           
            RCLCPP_INFO(node->get_logger(),"Invalid key press!!");
        }
        std::cout << "\n\r";
        refresh();
        
    // Implement state-specific logic based on the current state
    switch (current_state) {
        case State::IDLE:
            
            RCLCPP_INFO(node->get_logger(), "Idle state logic");          
            // ...
            break;
        case State::WORKING:
            RCLCPP_INFO(node->get_logger(), "Working state logic");
            // ...
            break;
        case State::FINISHED:           
            RCLCPP_INFO(node->get_logger(), "Finished state logic");
          
            // ...
            break;
    }
    std::cout << "\n\r";
    refresh();
    // Sleep or use a timer to control the update rate
   // std::this_thread::sleep_for(std::chrono::seconds(1));
}
    endwin(); 
    rclcpp::shutdown();
    return 0;
}
