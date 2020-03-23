#include "game/wallet.h"

Wallet::Wallet(int initialBalance) {
  peakBalance = balance = initialBalance;
}

void Wallet::gainMoney(int ammount) {
  balance += ammount;
  if(balance > peakBalance)
    peakBalance = balance;
}

void Wallet::loseMoney(int ammount) {
  balance -= ammount;
}

int Wallet::getBalance() {
  return balance;
}

int Wallet::getPeak() {
  return peakBalance;
}
