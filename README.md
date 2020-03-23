# transshipment

Game I made for this game jam: https://itch.io/jam/mini-jam-50-islands

# How to play?

You have a bunch of islands and the port. If you press on one of the islands, a menu will pop-up.

The islands are of three types:
1) Clients: they will request certain resources
2) Suppliers: they will supply you with certain resources
3) Gas stations: they will supply your boats with fuel.

There is also the port (you can click on it, just like with the islands). A menu with a shop will pop-up and you can buy boats from here. There are 6 ships available:
1) Standard ship
2) Better ship
3) Fast ship
4) Big cargo ship
5) Faster ship
6) Big fuel ship

I'm to tired to explain what each ship does, so please explore by yourself =)

There are also a few catches:
If you go bankrupt (your balance goes below 0), you lose
If you crash a ship in an island or another ship, you will lose 10000$. Also if your ship crashes in a previous crash site of two ships, the new ship will also crash (you can't see this though because I forgot to implement it :p)
If you hold an ice rock and a magma rock in the same ship, they will be lost (since the magma rock melts the ice rock and the ice rock extinguishes the magma rock)
If you hold a magma rock and gasoline in the same ship, the ship will be destroyed (therefore you will get another invisible crash site and 10000$ fine)
If you hold more than 5 uranium pieces, the ship will be destroyed due to a nuclear explosion that happens to only destroy the ship (hence another 10000$ fine and invisible crash site)


# How to compile?

Right now it's not the best moment to ask >:(

# Things used

SDL2.0, SDL_image and SDL_ttf
FFF Forward Font - https://www.1001fonts.com/fff-forward-font.html

