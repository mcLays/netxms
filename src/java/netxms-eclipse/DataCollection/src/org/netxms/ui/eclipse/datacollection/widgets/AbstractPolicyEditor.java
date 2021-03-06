package org.netxms.ui.eclipse.datacollection.widgets;

import java.util.HashSet;
import java.util.Set;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.texteditor.FindReplaceAction;
import org.netxms.client.objects.AgentPolicy;
import org.netxms.ui.eclipse.datacollection.widgets.helpers.PolicyModifyListener;

public abstract class AbstractPolicyEditor extends Composite
{
   Set<PolicyModifyListener> listeners = new HashSet<PolicyModifyListener>();
   AgentPolicy policy = null;  
   FindReplaceAction actionFindReplace = null;

   public AbstractPolicyEditor(Composite parent, int style)
   {
      super(parent, style);
   }

   /**
    * @param modifyListener
    */
   public void addModifyListener(PolicyModifyListener modifyListener)
   {
      listeners.add(modifyListener);
   }

   /**
    * @param modifyListener
    */
   public void removeModifyListener(PolicyModifyListener modifyListener)
   {
      listeners.remove(modifyListener);
   }

   /**
    * Execute all registered modify listeners
    */
   protected void fireModifyListeners()
   {
      for(PolicyModifyListener l : listeners)
         l.modifyParser();
   }

   public void updatePolicy(AgentPolicy policy)
   {
      this.policy = policy;   
      updateControlsFromPolicy();
   }

   /**
    * Update editor controls from policy
    */
   protected abstract void updateControlsFromPolicy();

   public abstract AgentPolicy getUpdatedPolicy();
   
   protected void createActions()
   {
   }
   
   public abstract boolean isFindReplaceRequired();

   public void setFindAndReplaceAction(FindReplaceAction actionFindReplace)
   {
      this.actionFindReplace = actionFindReplace;
   }
}
