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


#include "GraphicalTerminalCommand.h"
#include "Program.h"
#include "UserContext.h"
#include "PeacenetWorldStateActor.h"

AGraphicalTerminalCommand::AGraphicalTerminalCommand()
{
}

AGraphicalTerminalCommand::~AGraphicalTerminalCommand()
{
}

void AGraphicalTerminalCommand::NativeRunCommand(UConsoleContext * InConsole, TArray<FString> InArguments)
{
	if (!InConsole->GetUserContext()->GetDesktop())
	{
		InConsole->WriteLine(NSLOCTEXT("Peacegate", "NoGUI", "error: cannot connect to Xorg server (Is Peacegate Desktop running?)"));
		this->Complete();
		return;
	}

	UProgram* OpenedProgram = nullptr;
	InConsole->GetUserContext()->OpenProgram(this->ProgramAsset->ID, OpenedProgram, false);

	this->Complete();
}
