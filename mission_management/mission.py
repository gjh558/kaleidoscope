

class MissionStatus:
    UNDONE = 0
    DONE = 1
    UNSURE = 2
    
class Mission:
    uniq_id = 0
    def __init__(self, descrition, details, status):
        self.__description = descrition
        self.__details = details
        self.__status = status
        self.__id = Mission.uniq_id
        Mission.uniq_id += 1

    def set_description(self, description):
        self.__description = description
    def get_description(self):
        return self.__description

    def set_details(self, details):
        self.__details = details
    def get_details(self):
        return self.__details
    
    def set_status(self, status):
        self.__status = status
    def get_status(self):
        return self.__status
    
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

    def id(self):
        return self.__id
    
    def __cmp__(self, other):
        return self.__id == other.__id

# Test
if "__main__" == __name__:
    mission = Mission("First Mission", "This is my first mission' details", MissionStatus.UNDONE)
    print(mission.get_description())
    print(mission.get_details())
    print(mission.get_status())

    mission.set_create_time("2017-12-21")
    print(mission.get_create_time())
    print("ID %d" % mission.id())
    mission2 = Mission("Second Mission", "===", MissionStatus.UNDONE)
    print("ID %d" % mission2.id())
    
    
