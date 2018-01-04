from mission import Mission, MissionStatus

class Project:
   
    
    #def __init__(self, name):
    #    self.__missions = {}
    #    self.__name = name
    def __init__(self, name, description):
        self.__missions = {MissionStatus.UNDONE : [], MissionStatus.DONE : [], MissionStatus.UNSURE : []}
        self.__name = name
        self.__description = description

    def set_name(self, name):
        self.__name = name
    def get_name(self):
        return self.__name

    def set_description(self, description):
        self.__description = description
    def get_description(self):
        return self.__description
    
    def set_deadline(self, time):
        self.__deadline = time
    def get_deadline(self):
        return self.__deadline

    def add_mission(self, mission):
        status = mission.get_status()
        if (status != MissionStatus.UNSURE) and (status != MissionStatus.UNDONE) and (status != MissionStatus.DONE):
            print("Wrong mission status", status)
            return False
        self.__missions[status].append(mission)
        return True

    def remove_mission(self, mission):
        status = mission.get_status()
        if (status != MissionStatus.UNSURE) and (status != MissionStatus.UNDONE) and (status != MissionStatus.DONE):
            print("Wrong mission status", status)
            return False
        self.__missions[status].remove(mission);
        return True

    def get_missions(self, status):
        return self.__missions[status]
    def get_mission(self, status, index):
        return self.__missions[status][index]

# Test      
if __name__ == "__main__":
    p = Project("Adserver", "")
    p.set_deadline("2017-12-31")
    m1 = Mission("a mission", "details", MissionStatus.UNDONE);
    m2 = Mission("b mission", "details", MissionStatus.UNDONE);
    p.add_mission(m1);
    p.add_mission(m2);

    print("Project: %s" % p.get_name())
    print("Dealine: %s" % p.get_deadline())
    missions = p.get_missions(MissionStatus.UNDONE)
    for m in missions:
        print("-->%d: %s" % (m.id(), m.get_description()))
