#include <vector>

std::vector<int> the_lift(
  std::vector<std::vector<int>> &queues, int capacity) {
  /* Note, I have slightly altered this function header to remove the const declaration for queues as I wanted to make changes to the struct without
     deep copying for memory efficiency. It didn't seem as though I needed to maintain this struct based on the returns. However, if I had to return it 
     as in the questio, i.e. with each person at their respective floors, I would instead push_back any passenger I dropped off to their floor and may 
     need to add additional checks. */

  std::vector<int> ret = {0};
  std::vector<int> passengers;
  bool passengers_remaining = true;
  
  while(passengers_remaining){
    /* if there is a passenger remaining it will be noted when we go through loops below*/
    passengers_remaining = false;
    
    /* go up the floors */
    for(int i = 0; i < queues.size(); i++){

      bool floor_visited = false; /* flag to see if we have visited the floor*/

      /* Drop off people from the elevator */
      for(auto it = passengers.begin(); it != passengers.end();){
        if(*it == i){
          it = passengers.erase(it);
          floor_visited = true; //drop off ergo floor visited.
        } else { 
          it++; 
        }
      }

      /* Bring new passengers on to the elevator */
      for(auto it = queues[i].begin(); it != queues[i].end(); ){

        /* Determine if the passenger is going up*/
        if(*it > i){
          /* There was a passenger who wanted to go up therefore we have visited this floor. (this condition confused me for like half an hour lol, ty dinglemouse for clarifying fire_drill and making me realize)*/
          floor_visited = true;

          /* Add the passengers if we had the capacity. (Original had this combined with the above ) */
          if(passengers.size() < capacity){
            passengers.push_back(*it);
            it = queues[i].erase(it);
          } else {
            /* capacity met but passengers still remain, set flag to true to continue while loop */
            passengers_remaining = true;
          
            it++;
          }
        } else {
          it++;
        }
      }

      /* add floor to return vector if visited. */
      if(floor_visited && ret.back() != i){
        ret.push_back(i);
      }
    }

    /* go down the floors */
    for(int i = queues.size()-1; i >= 0 ; i--){

      bool floor_visited = false; /* flag to see if we have visited the floor*/

      /* Drop off people from the elevator */
      for(auto it = passengers.begin(); it != passengers.end();){
        if(*it == i){
          it = passengers.erase(it);
          floor_visited = true; //drop off ergo floor visited.
        } else { 
          it++; 
        }
      }

      /* Bring new passengers on to the elevator */
      for(auto it = queues[i].begin(); it != queues[i].end(); ){
        
        /* Determine if the passenger is going down */
        if(*it < i){
          /* There was a passenger who wanted to go down therefore we have visited this floor. */
          floor_visited = true;

          /* Add the passengers if we had the capacity. */
          if(passengers.size() < capacity){
            passengers.push_back(*it);
            it = queues[i].erase(it);
          } else {
            /* capacity met but passengers still remain, set flag to true to continue while loop */
            passengers_remaining = true;
          
            it++;
          }
        } else {
          it++;
        }
      }

      /* add floor to return vector if visited and not last in current return vector. */
      if(floor_visited && ret.back() != i){
        ret.push_back(i);
      }
    }
  }
  
  //If we did not end at floor 0 push 0 to back
  if(ret.back() > 0)
    ret.push_back(0);
  
  return ret;
}