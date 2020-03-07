Uogólniona reguła Jacksona: jeżeli maszyna jest wolna oraz co najmniej jedno zadanie jest gotowe do wykonywania, należy skierować do wykonywania dostępne zadanie najpilniejsze, to znaczy to z najdłuższym czasem dostarczania. r_i - moment dostępności zadania p_i - czas wykonywania zadania S_i - moment rozpoczęcia zadania C_i - moment zakończenia zadania

S_i >= r_i | S_i >= C_i-1 ===> S_i = max(r_i, C_i-1)
____________________________________________________
                        |
                        |
                        V
                 C_i = S_i + p_i
                 _______________
                        |
                        V
            C_i = max(r_i, C_i-1) + p_i
            ===========================

