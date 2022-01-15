package Info;

import java.util.*;

public interface IUser  {
    String getId();
    String getName();
    List<String> getFriends();
    int getNfriends();
    void setId(String id);
    void setName(String name);
    void setFriends(List<String> friends);
    void setNfriends(int nfriends);
    int compareTo(Object user);
}
