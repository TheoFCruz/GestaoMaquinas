from enum import Enum

# Guarda o estado de cada esp
status_dict: dict = {}

# Possiveis estados
class state(Enum):
    FREE = 0
    INUSE = 1
    MAINTENANCE = 2

# Atualiza o dicionario de estados com base na mensagem
def process_message(message: str) -> None:
    try: 
        message_list = message.split()

        espID = message_list[0]
        espStatus = state(int(message_list[1]))

        status_dict[espID] = espStatus
        print('Current states: ')
        for id, status in status_dict.items():
            print(f'{id}: {status.name}')
    except:
        print(f'Unable to process message: \'{message}\'')
