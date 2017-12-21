from enum import Enum

class MissionStatus(Enum):
    UNDONE = 0
    DONE = 1
    UNSURE = 2
    
class Mission:
    def __init__(self, descrition, details):
        self.__description = descrition
        self.__details = details
        self.__status = CREATE

    def set_create_time(self, time):
        self.__create_time = time
    def get_create_time(self):
        return self.__create_time

    def set_expected_finish_time(self, time):
        self.__finish_time = time
    def get_expected_finish_time(self):
        return self.__finish_time

    def set_progress(self, progress):
        self.__progress = progress
    def get_progress(self):
        return self.__progress

    
