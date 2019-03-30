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

#include "MailMessage.h"
#include "MailProvider.h"

void UMailMessage::Setup(UMailProvider* InProvider, int InMessageID)
{
    check(InProvider);
    check(InMessageID >= 0);

    this->MessageID = InMessageID;
    this->Provider = InProvider;
}

FEmail UMailMessage::GetMainMessage()
{
    for(auto& Message : this->Provider->GetMailMessages())
    {
        if(Message.ID == this->MessageID)
            return Message;
    }
    return FEmail();
}

TArray<FEmail> UMailMessage::GetReplies()
{
    TArray<FEmail> Replies;

    for(auto& Message : this->Provider->GetMailMessages())
    {
        if(Message.InReplyTo == this->MessageID)
            Replies.Add(Message);
    }

    return Replies;
}

FText UMailMessage::GetSubject()
{
    return FText::FromString(this->GetMainMessage().Subject);
}

bool UMailMessage::HasMission()
{
    return false;
}

bool UMailMessage::HasAttachments()
{
    return this->GetAttachmentCount();
}

int UMailMessage::GetAttachmentCount()
{
    return 0;
}