#ifndef __WALLET_H
#define __WALLET_H

class Wallet {
private:
  int balance, peakBalance;
public:
  Wallet(int initialBalance);
  
  void gainMoney(int ammount);
  
  void loseMoney(int ammount);
  
  int getBalance();
  
  int getPeak();
};

#endif
