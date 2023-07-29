/*******
    This example is implementation of Command Design Pattern
**************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class Document {
    public:
    virtual ~Document() {}
    virtual void open()         = 0;
    virtual void close()        = 0;
    virtual void copy()         = 0;
    virtual void paste()        = 0;
};

class TextDocument : public Document {
    public:
    virtual ~TextDocument() { }
    virtual void open() {
        std::cout << "Text Document open operation\n";
    }
    virtual void close() {
        std::cout << "Text Document close operation\n";
    }
    virtual void copy() {
        std::cout << "Text Document copy operation\n";
    } 
    virtual void paste() {
        std::cout << "Text Document paste operation\n";
    }        
};

class GraphicDocument : public Document {
    public:
    virtual ~GraphicDocument() { }
    virtual void open() {
        std::cout << "Graphic Document open operation\n";
    }
    virtual void close() {
        std::cout << "Graphic Document close operation\n";
    }
    virtual void copy() {
        std::cout << "Graphic Document copy operation\n";
    } 
    virtual void paste() {
        std::cout << "Graphic Document paste operation\n";
    }     
};

class Command {
    public:
        virtual ~Command() {}
        virtual void execute()  = 0;
};

class OpenCommand : public Command {
    Document    *m_doc;
    public:
    virtual ~OpenCommand()  { }
    OpenCommand(Document * doc) : m_doc(doc) {}
    virtual void execute() {
        m_doc->open();
    }
};

class CloseCommand : public Command {   
    Document        *m_doc;
    public:
    virtual ~CloseCommand() { }
    CloseCommand(Document * doc) : m_doc(doc) {}
    virtual void execute() {
        m_doc->close();
    }
};

class CopyCommand : public Command {   
    Document        *m_doc;
    public:
    virtual ~CopyCommand() { }
    CopyCommand(Document * doc) : m_doc(doc) {}
    virtual void execute() {
        m_doc->copy();
    }
};

class PasteCommand : public Command {   
    Document        *m_doc;
    public:
    virtual ~PasteCommand() { }
    PasteCommand(Document * doc) : m_doc(doc) {}
    virtual void execute() {
        m_doc->paste();
    }
};

template<class Receiver> 
class SimpleCommand : public Command {
    typedef void (Receiver::*Action)();
    Receiver    *m_recv;
    Action      m_act;
    public:  
        virtual ~SimpleCommand()    { }
        SimpleCommand(Receiver * recv, Action act) :
            m_recv(recv), m_act(act) { }
        virtual void execute() {
            (m_recv->*m_act)();
        }
};

class Zoom {
    public:
    void zoomIn() {
        std::cout << "Zoom In\n";
    }
    void zoomOut() {
        std::cout << "Zoom Out\n";
    }    
};


class MacroCommand : public Command {
    std::vector<Command *>  m_list_cmd;
    public:
    virtual ~MacroCommand() { }

    virtual void add(Command * cmd) { 
        m_list_cmd.push_back(cmd); 
    }
    virtual void remove(Command * cmd) {
        std::remove(m_list_cmd.begin(), m_list_cmd.end(), cmd);
    }    
    virtual void execute() {
        for(auto & elem : m_list_cmd) {
            elem->execute();
        }
    }
};


class CommandInvoker {
    Command * m_cmd;
    public:
    void set(Command * cmd) { m_cmd = cmd; }
    void execute() { m_cmd->execute(); }
};

int main() {

    {
        std::cout << "=== For Text Document ===\n";

        CommandInvoker cmd_invoker;

        std::unique_ptr<Document> text_doc = std::make_unique<TextDocument>();
        
        std::unique_ptr<Command> open_cmd = std::make_unique<OpenCommand>(text_doc.get());
        cmd_invoker.set(open_cmd.get());
        cmd_invoker.execute();
        
        auto simp_zoom_cmd = std::make_shared<Zoom>();
        std::unique_ptr<Command> zoom_in_cmd = std::make_unique<SimpleCommand<Zoom>>(simp_zoom_cmd.get(), &Zoom::zoomIn);
        cmd_invoker.set(zoom_in_cmd.get());
        cmd_invoker.execute();

        std::unique_ptr<Command> zoom_out_cmd = std::make_unique<SimpleCommand<Zoom>>(simp_zoom_cmd.get(), &Zoom::zoomOut);
        cmd_invoker.set(zoom_out_cmd.get());
        cmd_invoker.execute();


        std::unique_ptr<Command> copy_cmd = std::make_unique<CopyCommand>(text_doc.get());
        std::unique_ptr<Command> paste_cmd = std::make_unique<PasteCommand>(text_doc.get());

        auto macro_cmd = std::make_shared<MacroCommand>();
        macro_cmd->add(copy_cmd.get());
        macro_cmd->add(paste_cmd.get());
        cmd_invoker.set(macro_cmd.get());
        cmd_invoker.execute();

        std::unique_ptr<Command> close_cmd = std::make_unique<CloseCommand>(text_doc.get());
        cmd_invoker.set(close_cmd.get());
        cmd_invoker.execute();        
    }
    
    {
        std::cout << "\n=== For Graphic Document ===\n";

        CommandInvoker cmd_invoker;

        std::unique_ptr<Document> graph_doc = std::make_unique<GraphicDocument>();
        
        std::unique_ptr<Command> open_cmd = std::make_unique<OpenCommand>(graph_doc.get());
        cmd_invoker.set(open_cmd.get());
        cmd_invoker.execute();
        
        auto simp_zoom_cmd = std::make_shared<Zoom>();
        std::unique_ptr<Command> zoom_in_cmd = std::make_unique<SimpleCommand<Zoom>>(simp_zoom_cmd.get(), &Zoom::zoomIn);
        cmd_invoker.set(zoom_in_cmd.get());
        cmd_invoker.execute();

        std::unique_ptr<Command> zoom_out_cmd = std::make_unique<SimpleCommand<Zoom>>(simp_zoom_cmd.get(), &Zoom::zoomOut);
        cmd_invoker.set(zoom_out_cmd.get());
        cmd_invoker.execute();


        std::unique_ptr<Command> copy_cmd = std::make_unique<CopyCommand>(graph_doc.get());
        std::unique_ptr<Command> paste_cmd = std::make_unique<PasteCommand>(graph_doc.get());

        auto macro_cmd = std::make_shared<MacroCommand>();
        macro_cmd->add(copy_cmd.get());
        macro_cmd->add(paste_cmd.get());
        cmd_invoker.set(macro_cmd.get());
        cmd_invoker.execute();


        std::unique_ptr<Command> close_cmd = std::make_unique<CloseCommand>(graph_doc.get());
        cmd_invoker.set(close_cmd.get());
        cmd_invoker.execute();
    }

    return 0;
}

/**********
    END OF FILE
****************/


