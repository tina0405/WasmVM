/*
Copyright (c) 2017 Luis Hsu, Shu-Min Cyu

Licensed under the Apache License, Version 2.0 (the "License");you may not use
this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and limitations
under the License.
*/

#include <Syscall.h>

std::map<std::string, ModuleInst*>* Syscall::moduleInsts = nullptr;
void Syscall::initSyscall(std::map<std::string, ModuleInst*>* moduleInsts) {
  Syscall::moduleInsts = moduleInsts;
}

void Syscall::handle(Store& store, Stack& coreStack) {
  // Check value count
  if (coreStack.valueNum < 1) {
    throw Exception("[unreachable] No value in the stack.", coreStack);
  }
  // Pop operand
  Value* operand = (Value*)coreStack.pop().data;
  if (operand->type != i32) {
    throw Exception("[unreachable] Operand type is not i32.", coreStack);
  }
  // Call
  switch (operand->data.i32) {
    case SYS_Read:
      // sys_read
      Call::sysRead(store, coreStack);
      break;
    case SYS_Write:
      // sys_write
      Call::sysWrite(store, coreStack);
      break;
    case SYS_Open:
      // sys_open
      Call::sysOpen(store, coreStack);
      break;
    case SYS_Close:
      // sys_close
      Call::sysClose(coreStack);
      break;
    case SYS_Poll:
      Call::sysPoll(store, coreStack);
      break;
    case SYS_Lseek:
      Call::sysLseek(coreStack);
      break;
    case SYS_Access:
      Call::sysAccess(store, coreStack);
      break;
    case SYS_Brk:
      Call::sysBrk(store, coreStack);
      break;
    case SYS_Pipe:
      Call::sysPipe(coreStack);
      break;
    case SYS_Select:
      Call::sysSelect(store, coreStack);
      break;
    case SYS_Dup:
      Call::sysDup(coreStack);
      break;
    case SYS_Exit:
      Call::sysExit(coreStack);
      break;
    case SYS_Kill:
      Call::sysKill(coreStack);
      break;
    case SYS_Pause:
      Call::sysPause(coreStack);
      break;
    case SYS_Getpid:
      Call::sysGetpid(coreStack);
      break;
    case SYS_Execve:
      Call::sysExecve(store, coreStack);
      break;
    case SYS_Fork:
      Call::sysFork(coreStack);
      break;
    case SYS_Vfork:
      Call::sysFork(coreStack);
      break;
    case SYS_Socket:
      Call::sysSocket(coreStack);
      break;
    case SYS_Shutdown:
      Call::sysShutdown(coreStack);
      break;
    case SYS_Connect:
      Call::sysConnect(store, coreStack);
      break;
    case SYS_Bind:
      Call::sysBind(store, coreStack);
      break;
    case SYS_Listen:
      Call::sysListen(coreStack);
      break;
    case SYS_Accept:
      Call::sysAccept(store, coreStack);
      break;
    case SYS_Sendto:
      Call::sysSendto(store, coreStack);
      break;
    case SYS_Recvfrom:
      Call::sysRecvfrom(store, coreStack);
      break;
    case SYS_Dup2:
      Call::sysDup2(coreStack);
      break;
    default:
      throw Exception("[unreachable] Non-available operand.", coreStack);
      break;
  }
  // Clean
  delete operand;
}
