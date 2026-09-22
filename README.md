# deadlock_double_tap_to_dash
This is a macro that parses a double tap command and creates a "sprint" button press for playing dead lock


working on linux x11
the dash key is \ so you can change that witch will alow you to free up buttons for other acations

for me I created this so that I could play with the double dash function because I come from unreal where that is normal and I like to have crouch on shift
deadlock makes use of alot of slides and so using control was just really bad feeling

it is important to note that dead lock dashes in the direction of the velocity of the player dash dir = player->linvel.normlized() somthing like that so you cant dash like its unreal
as in walk one direction then dash the other way dashing need to be in the direction the player is moving

this prob helps with lag comp and making the game less aim heavy



I have thought about checking to see if a dash would be valid

cuss right now u can just hold d and duble tap a to dash in d direction however as of know I will not be doing anything to check if that should or not should not be allowed 
this is basically abandon ware as of today as I only really made it for my personal use to make playing deadlock better for myself

