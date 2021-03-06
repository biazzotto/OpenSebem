/*
  OpenSebemAll.cpp - Biblioteca com todas as classes para o OpenSebem
  Copyright (c) 2011 Thiago Alvarenga Lechuga.  All right reserved.
  Written by Thiago A. Lechuga <thiagoalz@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <inttypes.h>
#include <string.h>

#include "OpenSebemAll.h"

//------------------------------------------------------------------------------

Activity::Activity(){

} 

void Activity::reset(){
}

void Activity::oneLoopIteration(){
}

void Activity::buttonPress(char b){
}
//------------------------------------------------------------------------------

Welcome::Welcome(){
    //TODO: Criar a tabela
    /*ButtonToActivityTable: {
        'ADIVINHE-O-NÚMERO': AdivinheONumero,
        'ADIÇÃO': Adicao,
        'MULTIPLICAÇÃO': Multiplicacao,
        'DIVISÃO': Divisao,
        'ARITMÉTICA': Aritmetica,
        'OPERAÇÃO': Operacao,
        'SIGA-ME': SigaMe,
        'MEMÓRIA-TONS': MemoriaTons,
        'NÚMERO-DO-MEIO': NumeroDoMeio,
        'SUBTRAÇÃO': Subtracao,
        'LIVRO': Livro
    }*/
} 

void Welcome::reset(){
    //TODO:
    //Display.clear();
    //Som.playSong(Songs.Welcome, function() {
           // Display.blinkSpecialDigit('*');
        //});
}

void Welcome::oneLoopIteration(){
}

void Welcome::buttonPress(char b){
    //TODO: montar a tabela
    //const newActivity = this->ButtonToActivityTable[b];
    //if (newActivity != NULL){
        //PB.setActivity(newActivity);
    //}else{
        //Som.lowBeep();
    //}
}
//------------------------------------------------------------------------------

Standby::Standby(){

}

void Standby::reset(){
    //Display.clear();
    //PB.disableKeyboard();
}

void Standby::oneLoopIteration(){
}

void Standby::buttonPress(char b){
}
//------------------------------------------------------------------------------

Prompt::Prompt(){
    this->maxDigitSize = 3;
    this->initialDigit = 7;
    this->done = false;
    this->promptCharacter = '-';
}

void Prompt::reset(){
    this->done = false;
    this->input = "   ";
    //TODO:
    //Display.clear(Prompt.initialDigit - Prompt.maxDigitSize + 1, Prompt.initialDigit);
    if (this->initialDigit == 4 && this->maxDigitSize == 2) {
        //Display.setSpecialDigit(' ');
        //Display.setSpecialDigit2(' ');
        //Display.blinkSpecialDigit(this->promptCharacter);
    } else {
        //Display.blinkDigit(this->initialDigit, this->promptCharacter);
    }
}

char *Prompt::getInput(){
    char *value = this->input;
    this->reset();
    return value;
}

bool Prompt::isEmpty(){
    return ( strcmp(this->input,"   ") == 0 );
}

void Prompt::oneLoopIteration(){
}

void Prompt::redrawPrompt(){
    //Display.showNumberAtDigit(this->input, this->initialDigit);
}

void Prompt::buttonPress(char b){
    if (b == OPB_ENTER) {
        if (this->isEmpty()) {
            //TODO:
            //Som.highBeep();
            return;
        }
        this->done = true;
        //PB.activity = PB.previousActivity;
        return;
    }

    char* numbers = "0123456789";
    if (strchr(numbers, 'b') != NULL) {
        //Som.lowBeep();
        //Display.disableBlink();
        if (this->initialDigit == 4 && this->maxDigitSize == 2) {
            //Display.setSpecialDigit('~');
            //Display.setSpecialDigit2('-');
        }
        switch (this->maxDigitSize) {
            case 1:
                //TODO:
                //this->input = b;
                break;
            case 2:
                //TODO:
                //this->input = this->input[1] + b;
                break;
            default:
                //TODO:
                //this->input = this->input[1] + this->input[2] + b;
                break;
        }
        this->redrawPrompt();
    } else {
        //TODO:
        //blink and HighBeep
        //Som.highBeep();
    }
}
//------------------------------------------------------------------------------

OpenSebem::OpenSebem() {
  bugfix= false;
  /* we are simulating all the bugs from the original machine */
  activity = NULL;
  ticks = 0;
  //delayTable: {},
  keyboardEnabled = true;
}

/*void OpenSebem::setup(uint8_t pin){
    this->_pin=pin;
}*/


void OpenSebem::init(){
    this->setActivity(STANDBY, false);
    this->reset();
    //TODO:
    //setInterval(this->oneLoopIteration, 100);
    //this->turnOnReminderTimer = setTimeout(this->showReminder, 3000);
}

void OpenSebem::resetDefaultVariables(){
    //TODO:
    //this->delayTable = {};
    this->enableKeyboard();
    this->ticks = 0;
    //Display.disableBlink();
}

void OpenSebem::reset(){
    this->resetDefaultVariables();
    if (this->activity != NULL)
        this->activity->reset();
}

void OpenSebem::delay(int ticks, int callback){
    //TODO:
    //this->delayTable[this->ticks + ticks] = callback;
}

void OpenSebem::oneLoopIteration(){
    this->ticks++;

    //TODO:
/*
    for (var delay in this->delayTable) {
        if (this->ticks >= delay) {
            this->delayTable[delay]();
            delete PB.delayTable[delay];
        }
    }
*/

    if (this->activity != NULL)
        this->activity->oneLoopIteration();
}

void OpenSebem::setActivity(Activity *m, bool keepScreenContents){
    //TODO:
    if (!keepScreenContents){
        //Display.clear();
    }
    this->resetDefaultVariables();
    this->activity = m;
    this->reset();
}

void OpenSebem::prompt(int initialDigit, int maxDigitSize, char promptCharacter){
    //TODO: Definir prompt na inicialização. (pretendo definir todas as atividades assim.
    //TODO: Verificar como essa funcao esta sendo utilizada no resto da aplicação para definir como tratar essa atribuicao condicional.
    //Provavelmente vou deixar sem
    PROMPT->initialDigit = initialDigit || 7;
    PROMPT->maxDigitSize = maxDigitSize || 3;
    PROMPT->promptCharacter = promptCharacter || '-';
    this->previousActivity = this->activity;
    this->setActivity(PROMPT, true);
}

void OpenSebem::buttonPress(char b){
    //TODO: Definir WELCOME e STANDBY na inicialização. (pretendo definir todas as atividades assim.
    switch (b) {
    case OPB_LIGA:
        this->setActivity(WELCOME, false);
        return;
    case OPB_DESLIGA:
        this->setActivity(STANDBY, false);
        return;
    default:
        if (this->keyboardEnabled && (this->activity != NULL)) {
            //if ( (this->activity != Welcome) && (b in Welcome.ButtonToActivityTable)) {//TODO:
                //Som.highBeep(); //TODO:
               // return;
           // }
            this->activity->buttonPress(b);
        }
    }
}

void OpenSebem::enableKeyboard(){
    this->keyboardEnabled = true;
}

void OpenSebem::disableKeyboard(){
    this->keyboardEnabled = false;
}

int OpenSebem::pointsByNumberOfTries(int t){
    switch (t) {
    case 0:
        return 10;
    case 1:
        return 6;
    case 2:
        return 4;
    }
    return 0;
}
