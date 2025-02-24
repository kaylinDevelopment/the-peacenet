/********************************************************************************
 * The Peacenet - bit::phoenix("software");
 * 
 * MIT License
 *
 * Copyright (c) 2018-2019 Michael VanOverbeek, Declan Hoare, Ian Clary, 
 * Trey Smith, Richard Moch, Victor Tran and Warren Harris
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * Contributors:
 *  - Michael VanOverbeek <alkaline@bitphoenixsoftware.com>
 *
 ********************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "TerminalCommand.h"
#include "CommandRunInstruction.h"
#include "TerminalCommandParserLibrary.h"
#include "CommandShell.generated.h"

UCLASS(BlueprintType, Abstract)
class PROJECTOGLOWIA_API ACommandShell : public ATerminalCommand
{
    GENERATED_BODY()

private:
    UPROPERTY()
    bool IsWaitingForInput = false;

    UPROPERTY()
    UConsoleContext* LastConsole = nullptr;

    UPROPERTY()
    TArray<FCommandRunInstruction> Instructions;

    UPROPERTY()
    bool IsWaitingForCommand = false;

    UPROPERTY()
    UConsoleContext* CurrentConsole = nullptr;

    UPROPERTY()
    ATerminalCommand* CurrentCommand = nullptr;

public:
    ACommandShell();

protected:
    virtual void Tick(float InDeltaTime) override;

protected:
    virtual bool AllowRedirection() { return false; }
    virtual bool AllowPipes() { return false; }
    virtual bool AutoCompleteSpecials() { return true; }
    virtual ATerminalCommand* GetCommand(FString Command) { return nullptr; }
    virtual bool RunSpecialCommand(UConsoleContext* InConsole, FString Command, TArray<FString> Arguments) { return false; }
    virtual FText GetShellPrompt() { return NSLOCTEXT("Shell", "DefaultPrompt", "> "); }

protected:
    UFUNCTION()
    void FinishSpecialCommand();

    UFUNCTION()
    void ExecuteNextCommand();

    UFUNCTION()
    FPeacegateCommandInstruction ParseCommand(const FString& InCommand, FString InHome, FText& OutputError);

    UFUNCTION()
    void ExecuteLine(FString Input);

    UFUNCTION()
    void CommandCompleted();

    UFUNCTION()
    void WriteShellPrompt();

    UFUNCTION()
    void WriteToHistory(FString Input);

public:
        UFUNCTION()
    static TArray<FString> Tokenize(const FString& InCommand, const FString& Home, FText& OutputError);	

};