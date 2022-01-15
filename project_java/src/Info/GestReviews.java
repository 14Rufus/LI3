package Info;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.*;
import java.util.AbstractMap.SimpleEntry;
import java.util.Map.Entry;
import java.util.stream.Stream;
import java.util.Collections;  
import java.util.Comparator;  
import java.util.stream.*;


public class GestReviews implements Serializable, IGestReviews{
    View v = new View();
    CatBusiness b = new CatBusiness();
    CatUsers u = new CatUsers();
    CatReviews r = new CatReviews();

    public void Controlador() throws IOException {
        CatBusiness b = new CatBusiness();
        CatUsers u = new CatUsers();
        CatReviews r = new CatReviews();
        boolean state = true;
        Scanner sc = new Scanner(System.in);
        v.inicio();
        sc.nextLine();
        v.clearScreen();
        //************************************************ MENU INICIAL ************************************/

        while (state) {
            v.menu();
            String escolha = sc.nextLine();
            switch (escolha) {
                case "0":
                    state = false;
                    break;
                    //*****************************LOAD FICHEIROS************************* */
                case "1":
                    load();

                    break;
                    //*******************************ESTATISTICAS***************************** */
                case "2":
                    consultas();
                    break;
                    //************************************QUERIES******************************** */
                case "3":
                    v.menuConsultasInterativas();
                    String escolha2 = sc.nextLine();
                    switch (escolha2) {
                        case "1":
                        Crono.start();
                            querie1();
                        Crono.stop();
                        v.print("Tempo da querie 1: " + Crono.getTime());
                            break;

                        case "2":
                            v.print("Escolha o mês pretendido:");
                            String month = sc.nextLine();
                            int mes = Integer.parseInt(month);
                            v.print("Escolha o ano pretendido");
                            String year = sc.nextLine();
                            int ano = Integer.parseInt(year);
                            Crono.start();
                            querie2(mes, ano);
                            Crono.stop();
                            v.print("Tempo da querie 2: " + Crono.getTime());
                            break;
                        
                        case "3":
                            v.print("Escolha o ID User pretendido:");
                            String user = sc.nextLine();
                            Crono.start();
                            
                            querie3(user);

                            Crono.stop();
                            v.print("Tempo da querie 3: " + Crono.getTime());
                            break;
                        

                        case "4":
                            v.print("Escolha o ID Business pretendido:");
                            String buss = sc.nextLine();
                            Crono.start();
                            
                            querie4(buss);

                            Crono.stop();
                            v.print("Tempo da querie 4: " + Crono.getTime());
                            break;


                        case "5":
                            v.print("Escolha o ID User pretendido:");
                            String user2 = sc.nextLine();
                            Crono.start();
                            
                            querie5(user2);
                            Crono.stop();
                            v.print("Tempo da querie 5: " + Crono.getTime());
                            break;

                        case "6":
                            v.print("Escolha a quantidade de negócios:");
                            String sizeS = sc.nextLine();
                            int size = Integer.parseInt(sizeS);
                            Crono.start();

                            querie6(size);
                            Crono.stop();
                            v.print("Tempo da querie 6: " + Crono.getTime());
                            break;

                        case "7":
                            Crono.start();
                            querie7();
                            Crono.stop();
                            v.print("Tempo da querie 7: " + Crono.getTime());
                            break;

                        case "8":
                            v.print("Escolha a quantidade de utilizadores:");
                            String size2 = sc.nextLine();
                            int size3 = Integer.parseInt(size2);
                            Crono.start();

                            querie8(size3);
                            Crono.stop();
                            v.print("Tempo da querie 8: " + Crono.getTime());
                            break;

                        case "9":
                            v.print("Escolha o ID Business pretendido:");
                            String cod_business = sc.nextLine();
                            v.print("Escolha o número de users pretendido:");
                            String size4 = sc.nextLine();
                            int size5 = Integer.parseInt(size4);

                            Crono.start();

                            querie9(cod_business, size5);
                            Crono.stop();
                            v.print("Tempo da querie 9: " + Crono.getTime());
                            break;

                        default:
                            v.print("Insira uma opção válida!");
                            break;
                    }
                    break;

                    //************************GUARDAR E CARREGAR ESTADO******************* */
                    case "4":
                    v.guardarCarregar();
                    String guarda = sc.nextLine();
                        switch(guarda){
                            case "0": 
                                v.menu();
                                break;
                            case"1":
                                v.print("****Gravar em binário***");
                                try{
                                    guardaEstado();
                                }
                                catch(FileNotFoundException e){
                                    v.print("Não foi possivel abrir o ficheiro");
                                }
                        
                                catch(IOException e){
                                    v.print("Não foi possivel gravar o ficheiro");
                                } 
                                break;

                            case "2":
                                v.print("*Carregando o Ficheiro");
                                try{
                                    carregaEstado();
                                }
                                catch(FileNotFoundException | ClassNotFoundException e){
                                    v.print("Não foi possivel encontrar o ficheiro");
                                }
                                break;
                            
                            default:
                                v.print("Insira uma opção válida!");
                                break;
                        }
                        break;


                default:
                    v.print("Insira uma opção válida!");
                    break;
            }

        }

    }

//*******************************MENU ESTATISTICAS******************************** */

    public void consultas() {
        Scanner sc = new Scanner(System.in);
        boolean state = true;
        while (state) {
            v.printConsultasMenu();
            Stats s = new Stats();
            String escolha = sc.nextLine();
            switch (escolha) {
                case "0":
                    state = false;
                    break;
                case "1":
                    s.statsGeral(u, b, r);
                    v.printConsultasGeral(s);
                    sc.nextLine();
                    break;
                case "2":
                    StatsMes sm = new StatsMes();
                    v.print("Insira o ano que pretende consultar\n");
                    int ano = Integer.parseInt(sc.nextLine());
                    sm.setAno(ano);
                    sm.preencheTabela(r);
                    v.printConsultasMes(sm);
                    sc.nextLine();
                    break;
                
                default:
                    v.print("Insira uma opção válida!");
                    break;
            }
        }


    }

    //***********************************MENU LOAD******************************* */
    public void load() throws IOException {
        Scanner sc = new Scanner(System.in);
        boolean state = true;
        while (state) {
            v.printMenuCarregamento();
            String escolha = sc.nextLine();
            switch (escolha) {
                case "0":
                    state = false;
                    break;
                case "1":
                try{
                    loadDefault();
                } catch (Exception e) {
                    v.print(e.getMessage());
                }
                    state = false;
                    break;
                case "2":
                    v.print("Escreva o path para o ficheiro de Users:\n");
                    String users = sc.nextLine();
                    v.print("Escreva o path para o ficheiro de Businesses:\n");
                    String businesses = sc.nextLine();
                    v.print("Escreva o path para o ficheiro de Reviews:\n");
                    String reviews = sc.nextLine();
                    v.print("Escreva o que divide os campos do ficheiro csv:\n");
                    String divisor = sc.nextLine();
                    loadPersonalizado(users, businesses, reviews, divisor);
                    state = false;
                    break;
                default:
                    v.print("Insira uma opção válida!");
                    break;
            }
        }
    }


    public void loadDefault() throws IOException, InterruptedException {
        Crono.start();
        r.setFicheiro("Files/reviews_1M.csv");
        b.setFicheiro("Files/business_full.csv");
        u.setFicheiro("Files/users_full.csv");
        Thread thread_utilizadores = new Thread(new Runnable(){
            public void run(){
                try{
                u.parseUsers("Files/users_full.csv",";");
                }
                catch(Exception e) {
                    v.print(e.getMessage());
                }
            }
        });
        thread_utilizadores.start();


        Thread thread_business = new Thread(new Runnable(){
            public void run(){
                try{
                    b.parseBusiness("Files/business_full.csv", ";");
                }
                catch(Exception e) {
                v.print(e.getMessage());
                }
            }
        });
        thread_business.start();
        thread_utilizadores.join();
        thread_business.join();


        r.parseReviews("Files/reviews_1M.csv", u, b, ";");



        Crono.stop();
        v.print("O tempo de leitura decorrido foi: " + Crono.getTime());
        //for(Map.Entry<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> entry : r.getCatalogo().entrySet()){
       //     v.print(entry.getKey());
        //    v.print(entry.getValue());
        //}
    }

    public void loadPersonalizado(String pathUsers,String pathBusiness, String pathReviews, String divisor) throws FileNotFoundException {
        Crono.start();
        try {
            r.setFicheiro(pathReviews);
            b.setFicheiro(pathBusiness);
            u.setFicheiro(pathUsers);
            Thread thread_utilizadores = new Thread(new Runnable(){
                public void run(){
                    try{
                        u.parseUsers(pathUsers,divisor);
                    }
                    catch(Exception e) {
                        v.print(e.getMessage());
                    }
                }
            });
            thread_utilizadores.start();

            Thread thread_business = new Thread(new Runnable(){
                public void run(){
                    try{
                    b.parseBusiness(pathBusiness, divisor);
                }
                catch(Exception e) {
                    v.print(e.getMessage());
                }
            }
        });
        thread_business.start();
        thread_utilizadores.join();
        thread_business.join();

        r.parseReviews(pathReviews, u, b, divisor);
        Crono.stop();
        v.print("O tempo de leitura decorrido foi: " + Crono.getTime());
        } catch (Exception e){
            throw new FileNotFoundException();
        }
    }


    //*********************************ESTATISTICAS***************************** */





    //********************************GUARDAR E CARREGAR ESTADO************************* */

    public void carregaEstado() throws FileNotFoundException, IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream("GuestReviews.dat");
        ObjectInputStream ois = new ObjectInputStream(fis);

        GestReviews novo = (GestReviews) ois.readObject();
        // cria um menu novo e é preciso alterar a gestão total para dar load aos dados
        ois.close();
        this.b = novo.b;
        this.r = novo.r;
        this.u = novo.u;
    }



    public void guardaEstado() throws FileNotFoundException, IOException{
        FileOutputStream fos = new FileOutputStream("GuestReviews.dat");
        ObjectOutputStream oos = new ObjectOutputStream(fos);

        oos.writeObject(this); 
        oos.flush();
        oos.close();
    }






    
//***************************************EXECUCAÇÃO DAS QUERIES***************************** */

//*********************+Querie 1***********************+
//Retorna a lista ordenada de businesses nao avaliados ou seja que nao estao contidos nas reviews
//Neste metodo so retorna a TreeSet por na View pede para se retornar um par ou dois prints: um da lista e outro
// do size da lista



    public void querie1(){
        TreeSet<String> q1 = new TreeSet<>();
        for(Map.Entry<Character,  TreeMap<String,Business>> entry_catalogo : b.getCatalogo().entrySet()){
            for(Map.Entry<String,Business> entry_business : b.getCatalogo().get(entry_catalogo.getKey()).entrySet()){
                String business_id = entry_business.getKey();
                if(!r.getCatalogo().containsKey(business_id)){
                    q1.add(business_id);
                }
            }
        }
        v.print(q1.toString());
        v.print("O Número de Negócios nunca avaliados é : " + q1.size());

        
    }


    //************************** Querie 2 *************

    //Compara o ano e o mes;month-1 pois o java tem os meses de 0 a 11;
    //cria um set de reviews para adicionar todas as reviews num certo ano e mes
    // nessas reviews cria um set de users para nao existir repetidos e adiciona o id
    //por fim retorna o valor total de cada um.
    public void querie2(int month,int year){
        int nTotalReviews=0;
        TreeSet<String> userDistintos = new TreeSet<>();
        SimpleEntry<Integer,Integer> dataRecebida = new SimpleEntry<>(year,month-1);
        for(Map.Entry<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> entry_reviews : r.getCatalogo().entrySet()){
            if(r.getCatalogo().get(entry_reviews.getKey()).get(dataRecebida)!= null){
                for(Map.Entry<String,List<Review>> entry_users : r.getCatalogo().get(entry_reviews.getKey()).get(dataRecebida).entrySet()){
                nTotalReviews += entry_users.getValue().size();
                userDistintos.add(entry_users.getKey());
                }
            }
        }
        v.print("O número total global de reviews no mês " + month + " e ano " + year + " foi de : " + nTotalReviews);
        v.print("O número total de users distintos no mês " + month + " e ano " + year + " foi de : " + userDistintos.size());
    }

    //***************************querie 3 *******************
    //por cada mes compara o user id na review e se existir, conta as reviews efetuadas
    //calcula a media dada pelo user e quantos negocios diferentes avaliou
    public void querie3(String id_user){
        TreeMap<Integer,Integer> res = new TreeMap<>();
        TreeMap<Integer,TreeSet<String>> businessDistintos = new TreeMap<>();
        TreeMap<Integer,List<Float>> classificacao = new TreeMap<>();
        for(Map.Entry<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> entry_reviews : r.getCatalogo().entrySet()){
            for(Map.Entry<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>> entry_data : r.getCatalogo().get(entry_reviews.getKey()).entrySet()){
                SimpleEntry<Integer,Integer> data = entry_data.getKey();
                if(entry_data.getValue().get(id_user)!=null){
                    for(Review re : entry_data.getValue().get(id_user)){
                        if(businessDistintos.containsKey(data.getValue()))
                            businessDistintos.get(data.getValue()).add(re.getBusiness_id());
                        else{
                            TreeSet<String> nome = new TreeSet<>();
                            nome.add(re.getBusiness_id());
                            businessDistintos.put(data.getValue(), nome);
                        }
                        if(classificacao.containsKey(data.getValue())){
                            classificacao.get(data.getValue()).add(re.getStars());
                        }
                        else{
                            ArrayList<Float> cla = new ArrayList<>();
                            cla.add(re.getStars());
                            classificacao.put(data.getValue(), cla);
                        }
                    }
                    if(res.containsKey(data.getValue())){
                        res.put(data.getValue(), (res.get(data.getValue())+ entry_data.getValue().get(id_user).size()));
                    }
                    else{
                        res.put(data.getValue(), entry_data.getValue().get(id_user).size());
                    }
                }
            }
        }
        v.print("**************** Total de Reviews por Mês ****************");
        for(Map.Entry<Integer,Integer> entry  : res.entrySet()){
            v.print("Mês: " + (entry.getKey()+1) + " - Total de reviews: " + entry.getValue());
        }
        v.print("**************** Total de Negocios Distintos por Mês ****************");
        for(Map.Entry<Integer,TreeSet<String>> entry  : businessDistintos.entrySet()){
            v.print("Mês: " + (entry.getKey()+1) + " - Total de negocios distintos : " + entry.getValue().size());
        }
        v.print("**************** Média de Classificação por Mês ****************");
        for(Map.Entry<Integer,List<Float>> entry  : classificacao.entrySet()){

            float total= 0;
            for(int j =0;j<entry.getValue().size(); j++){
                total+=entry.getValue().get(j);
            }
            v.print("Mês: " + (entry.getKey()+1) + " - Média de classificação : " + total/entry.getValue().size());
        }
        
    }

    // ****************************querie 4 *******************
    //por cada mes compara o business id na review e se existir, conta qtd reviews obtidas
    //calcula a media dada pelo user e quantos users diferentes avaliaram
    public void querie4(String id_business){
        TreeMap<Integer,Integer> res = new TreeMap<>();
        TreeMap<Integer,TreeSet<String>> userDistintos = new TreeMap<>();
        TreeMap<Integer,List<Float>> classificacao = new TreeMap<>();
        if(r.getCatalogo().get(id_business)!=null){
            
            for(Map.Entry<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>> entry_data : r.getCatalogo().get(id_business).entrySet()){
                SimpleEntry<Integer,Integer> data = entry_data.getKey();
                for(Map.Entry<String,List<Review>> entry_review : r.getCatalogo().get(id_business).get(data).entrySet()){
                    if(userDistintos.containsKey(data.getValue()))
                        userDistintos.get(data.getValue()).add(entry_review.getKey());
                    else{
                        TreeSet<String> users = new TreeSet<>();
                        users.add(entry_review.getKey());
                        userDistintos.put(data.getValue(),users);
                    }
                    if(res.containsKey(data.getValue()))
                    res.put(data.getValue(),res.get(data.getValue()) + entry_review.getValue().size());
                    else{
                        res.put(data.getValue(), entry_review.getValue().size());
                    }
                    for(Review re : entry_review.getValue()){
                        if(classificacao.containsKey(data.getValue())){
                            classificacao.get(data.getValue()).add(re.getStars());
                        }
                        else{
                            ArrayList<Float> cla = new ArrayList<>();
                            cla.add(re.getStars());
                            classificacao.put(data.getValue(), cla);
                        }
                    }
                }
            }
        }

        v.print("**************** Total de Reviews por Mês ****************");
        for(Map.Entry<Integer,Integer> entry  : res.entrySet()){
            v.print("Mês: " + (entry.getKey()+1) + " - Total de reviews: " + entry.getValue());
        }
        v.print("**************** Total de Users Distintos por Mês ****************");
        for(Map.Entry<Integer,TreeSet<String>> entry  : userDistintos.entrySet()){
            v.print("Mês: " + (entry.getKey()+1) + " - Total de negocios distintos : " + entry.getValue().size());
        }
        v.print("**************** Média de Classificação por Mês ****************");
        for(Map.Entry<Integer,List<Float>> entry  : classificacao.entrySet()){

            float total= 0;
            for(int j =0;j<entry.getValue().size(); j++){
                total+=entry.getValue().get(j);
            }
            v.print("Mês: " + (entry.getKey()+1) + " - Média de classificação : " + total/entry.getValue().size());
        }
}
    // ****************************querie 5 *******************



    
    public void querie5(String codUser){
        TreeMap<String,Integer> res= new TreeMap<>();
        for(Map.Entry<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> entry_reviews : r.getCatalogo().entrySet()){
            for(Map.Entry<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>> entry_data : r.getCatalogo().get(entry_reviews.getKey()).entrySet()){
                if(entry_data.getValue().get(codUser)!=null){
                    if(res.containsKey(entry_reviews.getKey()))
                        res.put(entry_reviews.getKey(),res.get(entry_reviews.getKey() + entry_data.getValue().get(codUser).size()));
                    else{
                        res.put(entry_reviews.getKey(), entry_data.getValue().get(codUser).size());
                    }
                }

            }
        }


    TreeMap<String,Integer> last = new TreeMap<>();
        for(Map.Entry<String, Integer> entry : res.entrySet()){
            last.put(b.getCatalogo().get(entry.getKey().charAt(0)).get(entry.getKey()).getName(),entry.getValue());
        }
        
        
        for(Map.Entry<String, Integer> entry : last.entrySet()){
        v.print("Negócio: " + entry.getKey());
        v.print("Quantidade de reviews no negócio: " + entry.getValue());
        }
}


    // ****************************querie 6 *******************


    public void querie6(int size) {
        HashMap<Integer, String> b = new HashMap<>();
        for (String id : r.getCatalogo().keySet()) {

            int nTotalReviews = 0;
            for (TreeMap<String, List<Review>> rev : r.getCatalogo().get(id).values())
                for (List<Review> cena : rev.values())
                    nTotalReviews += cena.size();
            b.put(nTotalReviews, id);
        }

        for(int i = 0;i<size &&b.size()!=0;i++){
            int max = b.keySet().stream().max(Integer::compare).get();
            v.print((i+1) + "->Id:" + b.get(max) + " Número de Reviews:" + max + '\n');
            b.remove(max);
        }
    }



    // ****************************querie 7 *******************

    public void querie7() {
        HashMap<String, ArrayList<String>> map = new HashMap<>();
        for (TreeMap<String, Business> tree : b.getCatalogo().values())
            for (Business busi : tree.values()) {
                if (map.containsKey(busi.getCity())) map.get(busi.getCity()).add(busi.getId());
                else {
                    ArrayList<String> lista = new ArrayList<>();
                    lista.add(busi.getId());
                    map.put(busi.getCity(), lista);
                }
            }
            for (String cidade : map.keySet()) {
                HashMap<Integer,String> res = new HashMap<>();
                    for (String id : map.get(cidade)){
                        int nTotalReviews = 0;
                        if(r.getCatalogo().get(id) != null) {
                            for (TreeMap<String, List<Review>> rev : r.getCatalogo().get(id).values())
                                for (List<Review> cena : rev.values())
                                    nTotalReviews += cena.size();
                        }
                        res.put(nTotalReviews,id);

                    }
                v.print("->"+cidade+"<-\n");
                for (int i = 0; i < 3 && res.size() != 0; i++) {
                    int max = res.keySet().stream().max(Integer::compare).get();
                    v.print((i + 1) + "->Id:" + res.get(max) + " Número de Reviews:" + max + '\n');
                    res.remove(max);
                }
            }
    }

    //***************************** querie 8 ************************ */

    public void querie8(int size){
        Set<String> list = new TreeSet<>();
        for (TreeMap<String,User> t : u.getCatalogo().values())
            list.addAll(t.keySet());

        HashMap<Integer, String> res = new HashMap<>();
        for (String id : list){
            int total =0;
            for (HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>> rev : r.getCatalogo().values())
                for (TreeMap<String,List<Review>> tree : rev.values())
                    if(tree.containsKey(id)){
                        total++;
                    }
            res.put(total,id);
        }

        for (int i = 0; i < size && res.size() != 0; i++) {
            int max = res.keySet().stream().max(Integer::compare).get();
            v.print((i + 1) + "->Id:" + res.get(max) + " Número de Reviews:" + max + '\n');
            res.remove(res.get(max));
        }
    }

//***************************** querie 9 ************************ */

    public void querie9(String cod_business, int x) {
        TreeMap<String, Integer> userDistintos = new TreeMap<>();
        TreeMap<String, List<Float>> classificacao = new TreeMap<>();
        if (r.getCatalogo().get(cod_business) != null) {
            for (Map.Entry<SimpleEntry<Integer, Integer>, TreeMap<String, List<Review>>> entry_data : r.getCatalogo().get(cod_business).entrySet()) {
                for (Map.Entry<String, List<Review>> entry_user : r.getCatalogo().get(cod_business).get(entry_data.getKey()).entrySet()) {
                    if (!userDistintos.containsKey(entry_user.getKey())) {
                        userDistintos.put(entry_user.getKey(), entry_user.getValue().size());
                    } else {
                        userDistintos.put(entry_user.getKey(), userDistintos.get(entry_user.getKey()) + entry_user.getValue().size());
                    }
                    for (Review re : entry_user.getValue()) {

                        if (!classificacao.containsKey(entry_user.getKey())) {
                            ArrayList<Float> cla = new ArrayList<>();
                            cla.add(re.getStars());
                            classificacao.put(entry_user.getKey(), cla);

                        } else {
                            classificacao.get(entry_user.getKey()).add(re.getStars());
                        }
                    }

                }
            }
        }
        int tamanho = 0;
        for (Map.Entry<String, List<Float>> entry : classificacao.entrySet()) {
            if(tamanho == x){
                break;
            }else{
                tamanho++;}
            float total = 0;
            for (int j = 0; j < entry.getValue().size(); j++) {

                total += entry.getValue().get(j);

            }


            System.out.println("user: " + entry.getKey() + " tem " + userDistintos.get(entry.getKey()) + " reviews, com classificação: " + (total / entry.getValue().size()));
        }
    }


}