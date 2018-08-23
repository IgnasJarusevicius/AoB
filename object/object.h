#ifndef OBJECT_H
#define OBJECT_H
#include "ranged.h"
#include "damage.h"

//------------------------------------------------------------------------------         
class Orc: public Character
{
      public: Orc(float,float);
      } ; 
      
//------------------------------------------------------------------------------          
class Skel_War: public Character
{
      public: Skel_War(float,float);
      } ; 
      
//------------------------------------------------------------------------------    
class Pirate: public Character
{
      public: Pirate(float,float);
      } ; 
      
//------------------------------------------------------------------------------          
class Barbar: public Character
{
      public: Barbar(float,float);
      } ; 

//------------------------------------------------------------------------------          
class Viking: public Character
{
      public: Viking(float,float);
      } ;

//------------------------------------------------------------------------------                
class Lava: public Character
{
      public: Lava(float,float);
      } ;  

//------------------------------------------------------------------------------          
class Knight: public Character
{
      public: Knight(float,float);
      } ;

//------------------------------------------------------------------------------          
class Dwarf: public Character
{
      public: Dwarf(float,float);
      } ;    
      
//------------------------------------------------------------------------------    
class Skel_Arch: public Ranged
{
      public: Skel_Arch(float,float);
      };

//------------------------------------------------------------------------------    
class Hunter: public Ranged
{
      public: Hunter(float,float);
      };

//------------------------------------------------------------------------------          
class Archer: public Ranged
{
      public: Archer(float,float);
      };

//------------------------------------------------------------------------------          
class Tree: public Game_Object
{
      public: Tree(float, float);
      };

//------------------------------------------------------------------------------    
class Rock: public Game_Object
{
 public: Rock(float,float);
 };
//------------------------------------------------------------------------------          
#endif

 

      
       
                 

 

 
 
 

 


 
      

