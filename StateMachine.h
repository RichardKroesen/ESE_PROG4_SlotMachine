#ifndef STATEMACHINE_H
#define STATEMACHINE_H

typedef int error_t;

typedef enum { NOERR } error_e;

typedef enum { S_NO, S_START, S_INIT, S_STAKEAMOUNT,
              S_PROCESS_100EU, S_PROCESS_50EU, S_STARTGAMBLE,
              S_PAYOUT }
             state_e;
typedef enum { E_NO, E_SEQ, E_INIT, E_SPIN, E_INSERT_100EU, E_INSERT_50EU,
              E_ADD_100EU, E_ADD_50EU, E_PAY_BALANCE, E_NO_BALANCE,
              E_RESULT }
             event_e;

class MainWindow;

class StateMachine {
public:
   StateMachine(MainWindow* pDialog):
      pDialog(pDialog),
      currentState(S_START), userBalance(0) {}
   ~StateMachine() {}

   void handleEvent(event_e eventIn);
   state_e getCurrentState() const { return currentState; }

   void F_start();

private:
   MainWindow *pDialog;
   state_e currentState;
   volatile int userBalance;

   event_e statemachine(event_e eventIn);
};

#endif
