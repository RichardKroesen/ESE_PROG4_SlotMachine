#include "mainwindow.h"
#include "StateMachine.h"
#include "GambleEngine.h"

#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include <sstream>

void StateMachine::handleEvent(event_e eventIn) {
    // Handle sequential states.
    while (eventIn != E_NO) {
        eventIn = statemachine(eventIn);
    }
}

event_e StateMachine::statemachine(event_e eventIn) {

    //QString stateMesage;
    state_e nextState = S_NO;
    event_e eventOut = E_NO;

    // Sequential states must sent E_SEQ (= eventOut).
    // Sequential stepping ends with sending E_NO.
    switch(currentState) {
    case S_START:
        pDialog->setLogger("\n-state: Start");
        nextState = S_INIT;
        eventOut = E_SEQ;
        break;
    case S_INIT:
        pDialog->setLogger("-state: Init");
        userBalance = 0.0;
        pDialog->setLogger("  +Balance changed to: " + QString::number(userBalance));
        pDialog->setDisplay("Please, make your Event choice");
        pDialog->enableButtons(true);
        nextState = S_STAKEAMOUNT;
        eventOut = E_NO;  // Go waiting for external events: event driven
        break;

    case S_STAKEAMOUNT:
        pDialog->setLogger("-state: StakeAmount");
        pDialog->setDisplay("Balance: €" + QString::number(userBalance));

        switch(eventIn) {
        case E_INSERT_100EU:
            nextState = S_PROCESS_100EU;
            break;
        case E_INSERT_50EU:
            nextState = S_PROCESS_50EU;
            break;
        case E_SPIN:
            nextState = S_STARTGAMBLE;
            break;
        case E_PAY_BALANCE:
            nextState = S_PAYOUT;
            break;
        default:
            pDialog->setLogger("STAKEAMOUNT System ERROR: Unknown event");
            break;
        }
        eventOut = E_SEQ;
        break;

    case S_PROCESS_100EU:
        pDialog->setLogger("-state: Process_100EU");
        userBalance += 100;
        pDialog->setLogger("  +Balance changed to: " + QString::number(userBalance));

        pDialog->setDisplay("Balance: €" + QString::number(userBalance));
        nextState = S_STAKEAMOUNT;
        eventOut = E_NO;
        break;

    case S_PROCESS_50EU:
        pDialog->setLogger("-state: Process_50EU");
        userBalance += 50;
        pDialog->setLogger("  +Balance changed to: " + QString::number(userBalance));

        pDialog->setDisplay("Balance: €" + QString::number(userBalance));
        nextState = S_STAKEAMOUNT;
        eventOut = E_NO;
        break;

    case S_PAYOUT:
        pDialog->setLogger("-state: BalancePayout");

        if(userBalance != 0) {
            int moneyWithdraw = userBalance;
            userBalance = 0;
            pDialog->setLogger("  +Balance changed to: " + QString::number(userBalance));
            pDialog->setLogger("  +Money withdrew: " + QString::number(moneyWithdraw));
            pDialog->setDisplay("Money withdraw: €" + QString::number(moneyWithdraw),
                                "New Balance: €" + QString::number(userBalance), "Thanks for playing!");
        } else {
            pDialog->setLogger("  _Not allowed-->NO_BALANCE");
            pDialog->setDisplay("No payout. You have no balance.");
        }

        nextState = S_STAKEAMOUNT;
        eventOut = E_NO;
        break;

    case S_STARTGAMBLE:
        pDialog->setLogger("-state: StartGamble");

        if(userBalance == 0) {
            nextState = S_STAKEAMOUNT;
            eventOut = E_NO;
            pDialog->setLogger("  _Not allowed-->NO_BALANCE");
            pDialog->setDisplay("Please increase your balance to start a bet.");
        } else {
            int userBetAmount = userBalance;
            userBalance = 0;
            int* comboArray = gambleCombination();
            int factor = determinePayout(comboArray, sizeof(comboArray));
            int gambleResult = userBetAmount * factor;

            pDialog->setLogger("  +Gamble Result factor is: " + QString::number(factor) + " X");

            userBalance += gambleResult;
            pDialog->setLogger("  +Balance changed to: " + QString::number(userBalance));

            pDialog->setDisplay("Reels: "
                                + QString::number(comboArray[0])
                    + " | " + QString::number(comboArray[1])
                    + " | " + QString::number(comboArray[2]), "Reel Payout factor: "
                    + QString::number(factor)
                    + " on €" + QString::number(userBetAmount), "New Balance: €"
                    + QString::number(userBalance));
            nextState = S_STAKEAMOUNT;
            eventOut = E_NO;
        }
        break;

    default:
        pDialog->setLogger("Slotmachine System ERROR: Unknown state");
        eventOut = E_NO;
        break;
    }
    currentState = nextState;
    return eventOut;
}
