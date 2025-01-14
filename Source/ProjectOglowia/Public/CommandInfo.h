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
#include "RAMUsage.h"
#include "Engine/DataAsset.h"
#include "ManualPageAssetBase.h"
#include "CommandInfo.generated.h"

UCLASS(Blueprintable)
class PROJECTOGLOWIA_API UCommandInfo : public UManualPageAssetBase
{
	GENERATED_BODY()

public:
	// The usage syntax strings for the command. This is used internally while parsing command-line arguments. Each element in the array represents a different line in the resulting Docopt usage string. You do NOT need to include the "Usage: " delimeter as Peacenet will do this for you when the asset loads.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Help")
	TArray<FString> UsageStrings;

	// A C++ or Blueprint class inheriting from UTerminalCommand which holds the state of and handles running this command.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command")
	TSubclassOf<ATerminalCommand> CommandClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata")
	bool UnlockedByDefault = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Help")
	bool ShowInHelp = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Resource Usage")
	ERAMUsage RAMUsage = ERAMUsage::Low;

protected:
	virtual void BuildManualPage(UManualPageBuilder* InBuilder) override;
};