package Info;

import java.io.Serializable;
import java.math.RoundingMode;
import java.text.DecimalFormat;

public class View implements Serializable {
    /**
     * Método que imprime espaço no ecrã
     */
    public void clearScreen() {
        for (int i = 0; i < 3; ++i)
            System.out.println();
    }

    public void print(String s){

        System.out.println(s);
    }


    public void inicio(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n               .______________________.                 ");
        sb.append("\n               |.---------------------.|                ");
        sb.append("\n               || GEST REVIEWS APP    ||                ");
        sb.append("\n               ||     Grupo 19:       ||                ");
        sb.append("\n               ||   -André Vieira     ||                ");
        sb.append("\n               ||   -Francisco Andrade||                ");
        sb.append("\n               ||   -Joana Sousa      ||                ");
        sb.append("\n               ||_____________________||                ");
        sb.append("\n               /.-.-.-.-.-.-.-.-.-.-.-.\\               ");
        sb.append("\n               /.-.-.-.-.-.-.-.-.-.-.-.-\\               ");
        sb.append("\n               /.-.-.-.-.-.-.-.-.-.-.-.-.\\              ");
        sb.append("\n               /______//__________\\___o___\\           ");
        sb.append("\n               \\__________________________/             ");
        sb.append("\n-----------------------------------------------------\n");
        sb.append("                       Bem-Vindo                     \n");
        sb.append("-----------------------------------------------------\n");
        sb.append("                                                     \n");
        sb.append("Durante a execução do programa pode executar qualquer\n");
        sb.append(" dos comandos do menu, tendo em atenção que os dados \n");
        sb.append("     têm de ser carregados antes das consultas.      \n");
        sb.append("                                                     \n");
        sb.append("          Prima qualquer tecla para continuar!       \n");
        sb.append("-----------------------------------------------------\n");
        System.out.print(sb.toString());
    }

    /**
     * Método que apresenta o Menu Inicial
     */
    public void menu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n-----------------------------------------------------\n");
        sb.append("                       MENU\n");
        sb.append("-----------------------------------------------------\n");
        sb.append("1 - Carregar Estado\n");
        sb.append("2 - Consultar estatisticas\n");
        sb.append("3 - Consultas interativas\n");
        sb.append("4 - Gravar estado| Carregar estado\n");
        sb.append("\n");
        sb.append("0 | Sair\n");
        sb.append("-----------------------------------------------------\n");
        System.out.print(sb.toString());
    }

    public void guardarCarregar(){
        StringBuilder sb = new StringBuilder();
        System.out.println("--------------------------------------");
        System.out.println("\n[0] Voltar ao Menu Inicial ");
        System.out.println("\n[1] Guardar Estado");
        System.out.println("\n[2] Carregar Estado");
        sb.append("-----------------------------------------------------\n");
        System.out.print(sb.toString());
    }

    /**
     * Método que apresenta o menu das Consultas Interativas
     */
    public void menuConsultasInterativas(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n-------------------------------------------------------------------------------------------\n");
        sb.append("                                   CONSULTAS INTERATIVAS\n");
        sb.append("---+---------------------------------------------------------------------------------------\n");
        sb.append(" 1 | Lista ordenada alfabeticamente com os identificadores dos negócios nunca avaliados e o seu respetivo total;\n");
        sb.append(" 2 | Dado um mês e um ano (válidos), determinar o número total global de reviews realizadas e o número total de users distintos que as realizaram;\n");
        sb.append(" 3 | Dado um código de utilizador, determinar, para cada mês, quantas reviews fez, quantos negócios distintos avaliou e que nota média atribuiu;\n");
        sb.append(" 4 | Dado o código de um negócio, determinar, mês a mês, quantas vezes foi avaliado, por quantos users diferentes e a média de classificação;\n");
        sb.append(" 5 | Dado o código de um utilizador determinar a lista de nomes de negócios que mais avaliou (e quantos), ordenada por ordem decrescente de quantidade e, para quantidades iguais, por ordem alfabética dos negócios;\n");
        sb.append(" 6 | Determinar o conjunto dos X negócios mais avaliados (com mais reviews) em cada ano, indicando o número total de distintos utilizadores que o avaliaram (X é um inteiro dado pelo utilizador);\n");
        sb.append(" 7 | Determinar, para cada cidade, a lista dos três mais famosos negócios em termos de número de reviews;\n");
        sb.append(" 8 | Determinar os códigos dos X utilizadores (sendo X dado pelo utilizador) que avaliaram mais negócios diferentes, indicando quantos, sendo o critério de ordenação a ordem decrescente do número de negócios;\n");
        sb.append(" 9 | Dado o código de um negócio, determinar o conjunto dos X users que mais o avaliaram e, para cada um, qual o valor médio de classificação\n");
        sb.append("10 | Determinar para cada estado, cidade a cidade, a média de classificação de cada negócio.\n");
        sb.append(" 0 | Voltar\n");
        sb.append("---+----------------------------------------------------------------------------------------\n");
        System.out.print(sb.toString());
    }

    public void printMenuCarregamento(){
        final StringBuilder sb = new StringBuilder();

        sb.append("-------------------------------------------------------\n");
        sb.append("                  MENU DE CARREGAMENTO \n");
        sb.append("-------------------------------------------------------\n");
        sb.append("\n");
        sb.append("\n");
        sb.append("1 - Carregar ficheiro Default.\n");
        sb.append("2 - Carregar ficheiro Específico\n");
        sb.append("\n");
        sb.append("\n");
        sb.append("0 - Sair do Menu de Carregamento\n");
        sb.append("-------------------------------------------------------\n");

        System.out.println(sb.toString());
    }

    public void printConsultasMenu(){
        final StringBuilder sb = new StringBuilder();

        sb.append("-------------------------------------------------------\n");
        sb.append("                  MENU DE CONSULTAS \n");
        sb.append("-------------------------------------------------------\n");
        sb.append("\n");
        sb.append("\n");
        sb.append("1 - Consultar estatísticas gerais.\n");
        sb.append("2 - Consultar estatísticas mensais\n");
        sb.append("\n");
        sb.append("\n");
        sb.append("0 - Sair do Menu de Consultas\n");
        sb.append("-------------------------------------------------------\n");

        clearScreen();

        System.out.println(sb.toString());
    }

    public void printConsultasGeral(Stats s) {
        final StringBuilder sb = new StringBuilder();

        sb.append("-------------------------------------------------------\n");
        sb.append("       Informações sobre ficheiro de reviews lido \n");
        sb.append("-------------------------------------------------------\n");
        sb.append(" Ficheiro Users lido                        | ").append(s.getFicheiroU()).append('\n');
        sb.append(" Ficheiro Reviews lido                      | ").append(s.getFicheiroR()).append('\n');;
        sb.append(" Ficheiro Businesses lido                   | ").append(s.getFicheiroB()).append('\n');;
        sb.append(" Número Total de Reviews Errados            | ").append(s.getWrongReviews()).append('\n');
        sb.append(" Número Total de Reviews sem Impacto        | ").append(s.getReviewsSemImpacto()).append('\n');
        sb.append(" Número Total de Businesses                 | ").append(s.getTotalBusinesses()).append('\n');;
        sb.append(" Número Total de Businesses Avaliados       | ").append(s.getTotalBusinessesAvaliados()).append('\n');;
        sb.append(" Número Total de Businesses Não Avaliados   | ").append(s.getTotalBusinesses() - s.getTotalBusinessesAvaliados()).append('\n');;
        sb.append(" Número Total de Users                      | ").append(s.getTotalUsers()).append('\n');;
        sb.append(" Número Total de Users Com Reviews          | ").append(s.getTotalUsersAtivos()).append('\n');;
        sb.append(" Número Total de Users Sem Reviews          | ").append(s.getTotalUsers() - s.getTotalUsersAtivos()).append('\n');
        sb.append("          ->Prima qualquer tecla para sair<-\n");
        sb.append("-------------------------------------------------------\n");

        clearScreen();

        System.out.println(sb.toString());
    }

    public void printConsultasMes(StatsMes sm) {
        final StringBuilder sb = new StringBuilder();
        DecimalFormat df = new DecimalFormat("#.##");
        DecimalFormat dd = new DecimalFormat("#.##");
        df.setRoundingMode(RoundingMode.CEILING);
        dd.setRoundingMode(RoundingMode.CEILING);
        Double[] t = new Double[2];
        sb.append("---------------------------------------------------------------+\n");
        sb.append("               Informações sobre o ano de ").append(sm.getAno()).append('\n');
        sb.append("+--------------------------------------------------------------+\n");
        sb.append("| Mês  | Total de Reviews | Média de Reviews | Users distintos |\n");
        sb.append("+------+------------------+------------------+-----------------+\n");
        for (int mes = 0; mes < 9; mes++) {
            t = sm.getTabela()[mes];
            sb.append("|  ").append(mes+1).append("   |        ").append(dd.format(t[0])).append("      |        ").append(df.format(t[1])).append("      |       ").append(dd.format(t[2])).append("      |\n");
            sb.append("+------+------------------+------------------+-----------------+\n");
        }
        for (int mes = 10; mes < 12; mes++) {
            t = sm.getTabela()[mes];
            sb.append("|  ").append(mes+1).append("  |        ").append(dd.format(t[0])).append("      |        ").append(df.format(t[1])).append("      |       ").append(dd.format(t[2])).append("      |\n");
            sb.append("+------+------------------+------------------+-----------------+\n");
        }
        t = sm.getTabela()[12];
        sb.append("|Total |      ").append(dd.format(t[0])).append("       |        ").append(df.format(t[1])).append("      |       ").append(dd.format(t[2])).append("      |\n");
        sb.append("+------+------------------+------------------+-----------------+\n");
        sb.append("               >Prima qualquer tecla para sair<-\n");
        sb.append("+------+------------------+------------------+-----------------+\n");
        System.out.println(sb.toString());
    }


}
