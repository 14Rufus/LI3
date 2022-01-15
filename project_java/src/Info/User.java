package Info;

import java.io.Serializable;
import java.util.List;

public class User implements Serializable, Compare, IUser {
    private String id;
    private String name;
    private List<String> friends;
    private int nfriends;

    public User(){
        this.id = null;
        this.name = null;
        this.friends = null;
        this.nfriends = 0;
    }

    public User(String id, String name, List<String> friends, int nfriends) {
        this.id = id;
        this.name = name;
        this.friends = friends;
        this.nfriends = nfriends;
    }

    public User(User user){
        this.id = user.getId();
        this.name = user.getName();
        this.friends = user.getFriends();
        this.nfriends = user.getNfriends();
    }
    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public List<String> getFriends() {
       return this.friends;
    }

    public int getNfriends() {
        return nfriends;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setFriends(List<String> friends) {
        this.friends = friends;
    }

    public void setNfriends(int nfriends) {
        this.nfriends = nfriends;
    }

    public User clone(){
        return new User(this);
    }




    public String toString() {
        return  "Info.User -> Id:" + id + '\n' +
                "Nome: " + name + '\n' +
                "Número de amigos:" + nfriends + "\n" +
                "Lista de amigos:" + friends + "\n" ;
    }


    @Override
    public int compareTo(Object user) {
            User user1 = (User) user;
            if (this.getId().equals(user1.getId()))
                return 0;
            else
                return 1;
    
    }
}
